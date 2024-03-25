import unittest
import os, sys

import numpy as np

from parameterized import parameterized
from scipy import ndimage

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from generate import *


def load_test_cases() -> list:
    """加载测试用例

    Returns
    -------
    list
        存储测试用例的列表

    Notes
    -----
    _description_
    """
    return gen_tcs_randomly()