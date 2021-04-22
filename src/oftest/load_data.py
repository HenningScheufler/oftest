import pandas as pd
from itertools import islice
from pathlib import Path
from typing import List
import io
import os



def read_csv_geoField(filename: str) -> pd.DataFrame:

    field = pd.read_csv(filename, index_col=[0, 1, 2], header=None)
    field = field[field.iloc[:, -1] != 'empty']  # drop empty
    field = field.sort_index()

    return field


def read_functionObject(filename: str) -> pd.DataFrame:
    suffix = os.path.splitext(filename)[1]
    if suffix in ('.xy', '.raw'):
        return pd.read_csv(filename, comment='#',
                           delim_whitespace=True, header=None)
    elif suffix == '.csv':
        return pd.read_csv(filename)
    else:
        df = pd.read_csv(filename, comment='#',
                         sep='[() \t]+', engine='python', header=None)

        # drop last column if null
        if(pd.isnull(df.iloc[0, -1])):
            df.drop(df.columns[[-1, ]], axis=1, inplace=True)

        return df


def tail_log(log: str, nbytes: int = 1024) -> List[str]:
    file = Path(log)
    size = file.stat().st_size
    with open(log, 'rb') as logh:
        logh.seek(max(-nbytes, -size), io.SEEK_END)
        content = logh.read().decode()
        lines = content.splitlines()

    return lines

def head_log(log: str, N: int = 10) -> List[str]:
    with open(log) as logh:
        head = [x.rstrip('\n') for x in islice(logh, N)]
    return head


def case_status(log: str, nbytes: int = 8*1024) -> str:
    ERROR_KEYS = ["FOAM FATAL ERROR", "FOAM FATAL IO ERROR",
                  "FOAM exiting", "Foam::error"]

    lines = tail_log(log, nbytes)

    for line in lines:
        if 'End' == line:
            return 'completed'
        elif any(error in line for error in ERROR_KEYS):
            return 'error'
    return 'running'

def run_time(log: str, nbytes: int = 8*1024) -> List[float]:
    lines = tail_log(log,nbytes)
    timings = []
    for line in reversed(lines):
        if line.startswith("ExecutionTime"):
            for elem in line.split():
                try:
                    t = float(elem)
                    timings.append(t)
                except:
                    pass
            return timings
    return [-1,-1]


