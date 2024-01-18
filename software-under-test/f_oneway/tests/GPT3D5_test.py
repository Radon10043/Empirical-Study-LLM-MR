"""
Author: Radon
Date: 2023-12-05 15:20:27
LastEditors: Radon
LastEditTime: 2024-01-18 20:11:37
Description: Hi, say something
"""
from scipy.stats import f_oneway
from parameterized import parameterized
from utils import gen_tcs_randomly

import unittest

import numpy as np


def load_test_cases() -> list:
    """加载测试用例

    Returns
    -------
    list
        存有测试用例的列表

    Notes
    -----
    _description_
    """
    return gen_tcs_randomly()


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test2(self, g1: list, g2: list):
        """MR2: Adding the same constant to all elements in both groups, the result should not change."""
        # Get source output
        source_out = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        const = np.random.randint(1, 10)  # Random constant
        follow_g1 = [x + const for x in g1]
        follow_g2 = [x + const for x in g2]

        # Get follow-up output
        follow_out = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertAlmostEqual(source_out, follow_out)

    @parameterized.expand(load_test_cases)
    def test3(self, g1: list, g2: list):
        """MR3: Multiplying all elements in both groups by the same constant, the result should not change."""
        # Get source output
        source_out = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        const = np.random.randint(1, 10)  # Random constant
        follow_g1 = [x * const for x in g1]
        follow_g2 = [x * const for x in g2]

        # Get follow-up output
        follow_out = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertAlmostEqual(source_out, follow_out)

    @parameterized.expand(load_test_cases)
    def test4(self, g1: list, g2: list):
        """MR4: Reversing the order of elements in both groups, the result should not change."""
        # Get source output
        source_out = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        follow_g1 = list(reversed(g1))
        follow_g2 = list(reversed(g2))

        # Get follow-up output
        follow_out = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertAlmostEqual(source_out, follow_out)

    @parameterized.expand(load_test_cases)
    def test5(self, g1: list, g2: list):
        """MR5: Adding a constant to one group and subtracting the same constant from the other group, the result should not change."""
        # Get source output
        source_out = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        const = np.random.randint(1, 10)  # Random constant
        follow_g1 = [x + const for x in g1]
        follow_g2 = [x - const for x in g2]

        # Get follow-up output
        follow_out = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertAlmostEqual(source_out, follow_out)

    @parameterized.expand(load_test_cases)
    def test6(self, g1: list, g2: list):
        """MR6: Splitting one group into two equal subgroups, adding noise to the second subgroup, the result should not change."""
        # Get source output
        source_out = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        midpoint = len(g1) // 2
        follow_g1 = g1[:midpoint]
        noisy_g1 = [x + np.random.uniform(-1, 1) for x in g1[midpoint:]]
        follow_g1.extend(noisy_g1)

        # Get follow-up output
        follow_out = f_oneway(follow_g1, g2).pvalue

        # Verification
        self.assertAlmostEqual(source_out, follow_out)

    @parameterized.expand(load_test_cases)
    def test7(self, g1: list, g2: list):
        """MR7: Combining the two groups into one larger group without changing the order, the result should not change."""
        # Get source output
        source_out = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        combined_data = g1 + g2

        # Get follow-up output
        follow_out = f_oneway(combined_data).pvalue

        # Verification
        self.assertAlmostEqual(source_out, follow_out)

    @parameterized.expand(load_test_cases)
    def test8(self, g1: list, g2: list):
        """MR8: Multiplying one group by a constant and keeping the other group unchanged, the result should not change."""
        # Get source output
        source_out = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        const = np.random.randint(1, 10)  # Random constant
        follow_g1 = [x * const for x in g1]

        # Get follow-up output
        follow_out = f_oneway(follow_g1, g2).pvalue

        # Verification
        self.assertAlmostEqual(source_out, follow_out)

    @parameterized.expand(load_test_cases)
    def test9(self, g1: list, g2: list):
        """MR9: Sorting the data within each group in ascending order, the result should not change."""
        # Get source output
        source_out = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        follow_g1 = sorted(g1)
        follow_g2 = sorted(g2)

        # Get follow-up output
        follow_out = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertAlmostEqual(source_out, follow_out)

    @parameterized.expand(load_test_cases)
    def test10(self, g1: list, g2: list):
        """MR10: Removing outliers from both groups, the result should not change."""
        # Get source output
        source_out = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        follow_g1 = self.remove_outliers(g1)
        follow_g2 = self.remove_outliers(g2)

        # Get follow-up output
        follow_out = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertAlmostEqual(source_out, follow_out)

    @staticmethod
    def remove_outliers(data: list) -> list:
        q25, q75 = np.percentile(data, 25), np.percentile(data, 75)
        iqr = q75 - q25
        cut_off = 1.5 * iqr
        lower, upper = q25 - cut_off, q75 + cut_off
        return [x for x in data if x >= lower and x <= upper]

    @parameterized.expand(load_test_cases)
    def test11(self, g1: list, g2: list):
        """MR11: Swapping a subset of elements between the two groups, the result should not change."""
        # Get source output
        source_out = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        subset_size = min(len(g1), len(g2)) // 2
        follow_g1 = g1.copy()
        follow_g2 = g2.copy()
        subset_indices = np.random.choice(len(g1), subset_size, replace=False)

        for idx in subset_indices:
            follow_g1[idx], follow_g2[idx] = follow_g2[idx], follow_g1[idx]

        # Get follow-up output
        follow_out = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertAlmostEqual(source_out, follow_out)

    @parameterized.expand(load_test_cases)
    def test12(self, g1: list, g2: list):
        """MR12: Randomly shuffling both groups, the result should not change."""
        # Get source output
        source_out = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        np.random.shuffle(g1)
        np.random.shuffle(g2)

        # Get follow-up output
        follow_out = f_oneway(g1, g2).pvalue

        # Verification
        self.assertAlmostEqual(source_out, follow_out)

    @parameterized.expand(load_test_cases)
    def test13(self, g1: list, g2: list):
        """MR13: Combining one group with an empty group should yield the same result as the original non-empty group."""
        # Get source output
        source_out = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        empty_group = []
        follow_g1 = g1 + empty_group

        # Get follow-up output
        follow_out = f_oneway(follow_g1, g2).pvalue

        # Verification
        self.assertAlmostEqual(source_out, follow_out)

    @parameterized.expand(load_test_cases)
    def test14(self, g1: list, g2: list):
        """MR14: Repeating the elements within each group, the result should remain unchanged."""
        # Get source output
        source_out = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        follow_g1 = g1 * 2
        follow_g2 = g2 * 2

        # Get follow-up output
        follow_out = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertAlmostEqual(source_out, follow_out)

    @parameterized.expand(load_test_cases)
    def test15(self, g1: list, g2: list):
        """MR15: Scaling both groups by a constant factor, the result should remain unchanged."""
        # Get source output
        source_out = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        constant_factor = np.random.uniform(0.5, 2.0)
        follow_g1 = [x * constant_factor for x in g1]
        follow_g2 = [x * constant_factor for x in g2]

        # Get follow-up output
        follow_out = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertAlmostEqual(source_out, follow_out)

    @parameterized.expand(load_test_cases)
    def test16(self, g1: list, g2: list):
        """MR16: Appending a constant sequence to both groups, the result should remain unchanged."""
        # Get source output
        source_out = f_oneway(g1, g2).pvalue

        # Construct constant sequence
        constant_sequence = np.full(len(g1), 10)

        # Construct follow-up input
        follow_g1 = np.concatenate([g1, constant_sequence])
        follow_g2 = np.concatenate([g2, constant_sequence])

        # Get follow-up output
        follow_out = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertAlmostEqual(source_out, follow_out)

    @parameterized.expand(load_test_cases)
    def test17(self, g1: list, g2: list):
        """MR17: Adding a trend to both groups, the result should remain unchanged."""
        # Get source output
        source_out = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        trend = [i * 0.1 for i in range(len(g1))]  # Linear trend
        follow_g1 = [x + trend[i] for i, x in enumerate(g1)]
        follow_g2 = [x + trend[i] for i, x in enumerate(g2)]

        # Get follow-up output
        follow_out = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertAlmostEqual(source_out, follow_out)

    @parameterized.expand(load_test_cases)
    def test18(self, g1: list, g2: list):
        """MR18: Replacing a subset of elements with the mean of the group, the result should remain unchanged."""
        # Get source output
        source_out = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        subset_size = min(len(g1), len(g2)) // 2
        subset_indices = np.random.choice(len(g1), subset_size, replace=False)

        follow_g1 = g1.copy()
        follow_g2 = g2.copy()
        mean_g1 = np.mean(g1)
        mean_g2 = np.mean(g2)

        for idx in subset_indices:
            follow_g1[idx] = mean_g1
            follow_g2[idx] = mean_g2

        # Get follow-up output
        follow_out = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertAlmostEqual(source_out, follow_out)

    @parameterized.expand(load_test_cases)
    def test19(self, g1: list, g2: list):
        """MR19: Multiplying one group by another group element-wise, the result should not change."""
        # Get source output
        source_out = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        follow_g1 = [x * y for x, y in zip(g1, g2)]

        # Get follow-up output
        follow_out = f_oneway(follow_g1, g2).pvalue

        # Verification
        self.assertAlmostEqual(source_out, follow_out)

    @parameterized.expand(load_test_cases)
    def test20(self, g1: list, g2: list):
        """MR20: Replacing the values with its absolute values in both groups, the result should not change."""
        # Get source output
        source_out = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        follow_g1 = [abs(x) for x in g1]
        follow_g2 = [abs(x) for x in g2]

        # Get follow-up output
        follow_out = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertAlmostEqual(source_out, follow_out)

    @parameterized.expand(load_test_cases)
    def test21(self, g1: list, g2: list):
        """MR21: Each of the elements in both groups is added to the mean of the group, the result should not change."""
        # Get source output
        source_out = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        follow_g1 = [x + np.mean(g1) for x in g1]
        follow_g2 = [x + np.mean(g2) for x in g2]

        # Get follow-up output
        follow_out = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertAlmostEqual(source_out, follow_out)

    @parameterized.expand(load_test_cases)
    def test22(self, g1: list, g2: list):
        """MR22: Replacing a subset of elements in one group with the corresponding subset from the other group, the result should not change."""
        # Get source output
        source_out = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        subset_size = min(len(g1), len(g2)) // 2
        subset_indices = np.random.choice(len(g1), subset_size, replace=False)

        follow_g1 = g1.copy()
        follow_g2 = g2.copy()

        for idx in subset_indices:
            follow_g1[idx] = follow_g2[idx]

        # Get follow-up output
        follow_out = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertAlmostEqual(source_out, follow_out)

    @parameterized.expand(load_test_cases)
    def test23(self, g1: list, g2: list):
        """MR23: Scaling one group while inversely scaling the other group, the result should remain unchanged."""
        # Get source output
        source_out = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        scale_factor = np.random.uniform(0.5, 2.0)  # Random scale factor
        follow_g1 = [x * scale_factor for x in g1]
        follow_g2 = [x / scale_factor for x in g2]

        # Get follow-up output
        follow_out = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertAlmostEqual(source_out, follow_out)

    @parameterized.expand(load_test_cases)
    def test24(self, g1: list, g2: list):
        """MR24: Adding a polynomial trend to the second group, the result should not change."""
        # Get source output
        source_out = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        trend = [i**2 for i in range(len(g1))]  # Quadratic trend
        follow_g2 = [x + trend[i] for i, x in enumerate(g2)]

        # Get follow-up output
        follow_out = f_oneway(g1, follow_g2).pvalue

        # Verification
        self.assertAlmostEqual(source_out, follow_out)

    @parameterized.expand(load_test_cases)
    def test25(self, g1: list, g2: list):
        """MR25: Concatenating both groups with a reverse order of the second group, the result should remain unchanged."""
        # Get source output
        source_out = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        follow_g2 = list(reversed(g2))
        follow_combined = g1 + follow_g2

        # Get follow-up output
        follow_out = f_oneway(follow_combined).pvalue

        # Verification
        self.assertAlmostEqual(source_out, follow_out)

    @parameterized.expand(load_test_cases)
    def test26(self, g1: list, g2: list):
        """MR26: Incrementing the values in the first group while decrementing the values in the second group by the same constant factor, the result should not change."""
        # Get source output
        source_out = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        constant_factor = np.random.uniform(0.5, 2.0)  # Random constant factor
        follow_g1 = [x + constant_factor for x in g1]
        follow_g2 = [x - constant_factor for x in g2]

        # Get follow-up output
        follow_out = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertAlmostEqual(source_out, follow_out)

    @parameterized.expand(load_test_cases)
    def test27(self, g1: list, g2: list):
        """MR27: Randomly selecting one element from each group and swapping them, the result should remain unchanged."""
        # Get source output
        source_out = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        index_g1 = np.random.choice(len(g1))  # Random index for group 1
        index_g2 = np.random.choice(len(g2))  # Random index for group 2
        follow_g1 = g1.copy()
        follow_g2 = g2.copy()
        follow_g1[index_g1], follow_g2[index_g2] = follow_g2[index_g2], follow_g1[index_g1]

        # Get follow-up output
        follow_out = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertAlmostEqual(source_out, follow_out)

    @parameterized.expand(load_test_cases)
    def test28(self, g1: list, g2: list):
        """MR28: Adding a sorted version of one group to the other group, the result should not change."""
        # Get source output
        source_out = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        follow_g1 = g1 + sorted(g2)
        follow_g2 = g2 + sorted(g1)

        # Get follow-up output
        follow_out = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertAlmostEqual(source_out, follow_out)

    @parameterized.expand(load_test_cases)
    def test29(self, g1: list, g2: list):
        """MR29: Splitting both groups into two equal subgroups, taking the maximum value in each subgroup, the result should remain unchanged."""
        # Get source output
        source_out = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        split_point = len(g1) // 2
        follow_g1 = [max(g1[:split_point]), max(g1[split_point:])]
        follow_g2 = [max(g2[:split_point]), max(g2[split_point:])]

        # Get follow-up output
        follow_out = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertAlmostEqual(source_out, follow_out)

    @parameterized.expand(load_test_cases)
    def test30(self, g1: list, g2: list):
        """MR30: Reversing the order of elements in both groups and taking the absolute difference element-wise, the result should remain unchanged."""
        # Get source output
        source_out = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        reversed_g1 = list(reversed(g1))
        reversed_g2 = list(reversed(g2))
        follow_g1 = [abs(x - y) for x, y in zip(g1, g2)]
        follow_g2 = [abs(x - y) for x, y in zip(reversed_g1, reversed_g2)]

        # Get follow-up output
        follow_out = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertAlmostEqual(source_out, follow_out)

    @parameterized.expand(load_test_cases)
    def test31(self, g1: list, g2: list):
        """MR31: Replacing one group with its cumulative sum, the result should not change."""
        # Get source output
        source_out = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        follow_g1 = np.cumsum(g1)
        follow_g2 = g2

        # Get follow-up output
        follow_out = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertAlmostEqual(source_out, follow_out)

    @parameterized.expand(load_test_cases)
    def test32(self, g1: list, g2: list):
        """MR32: Appending a random normal distribution with the same mean and standard deviation to both groups, the result should not change."""
        # Get source output
        source_out = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        mean, std = np.mean(g1), np.std(g1)  # Use the same statistics for both groups
        random_values = np.random.normal(mean, std, len(g1))

        follow_g1 = np.concatenate([g1, random_values])
        follow_g2 = np.concatenate([g2, random_values])

        # Get follow-up output
        follow_out = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertAlmostEqual(source_out, follow_out)

    @parameterized.expand(load_test_cases)
    def test33(self, g1: list, g2: list):
        """MR33: Scaling the entire data range of one group while keeping the other group unchanged, the result should not change."""
        # Get source output
        source_out = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        range_g1 = max(g1) - min(g1)
        mean_g2 = np.mean(g2)
        follow_g1 = [mean_g2 + (x - min(g1)) * (mean_g2 / range_g1) for x in g1]

        # Get follow-up output
        follow_out = f_oneway(follow_g1, g2).pvalue

        # Verification
        self.assertAlmostEqual(source_out, follow_out)

    @parameterized.expand(load_test_cases)
    def test34(self, g1: list, g2: list):
        """MR34: Adding a random noise to both groups, the result should not change."""
        # Get source output
        source_out = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        noise = np.random.normal(0, 0.1, len(g1))  # Adding random noise
        follow_g1 = g1 + noise
        follow_g2 = g2 + noise

        # Get follow-up output
        follow_out = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertAlmostEqual(source_out, follow_out)

    @parameterized.expand(load_test_cases)
    def test35(self, g1: list, g2: list):
        """MR35: Shifting both groups by a constant factor, the result should not change."""
        # Get source output
        source_out = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        shift = np.random.uniform(1, 10)  # Random constant for shifting
        follow_g1 = [x + shift for x in g1]
        follow_g2 = [x + shift for x in g2]

        # Get follow-up output
        follow_out = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertAlmostEqual(source_out, follow_out)

    @parameterized.expand(load_test_cases)
    def test36(self, g1: list, g2: list):
        """MR36: Replacing the second group with its element-wise reciprocal, the result should not change."""
        # Get source output
        source_out = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        follow_g2 = [1 / x for x in g2]

        # Get follow-up output
        follow_out = f_oneway(g1, follow_g2).pvalue

        # Verification
        self.assertAlmostEqual(source_out, follow_out)

    @parameterized.expand(load_test_cases)
    def test37(self, g1: list, g2: list):
        """MR37: Replacing one of the groups with a duplicate, the result should not change."""
        # Get source output
        source_out = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        follow_g1 = g1.copy()
        follow_g2 = g1.copy()

        # Get follow-up output
        follow_out = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertAlmostEqual(source_out, follow_out)

    @parameterized.expand(load_test_cases)
    def test38(self, g1: list, g2: list):
        """MR38: Taking the logarithm of each element in both groups, the result should not change."""
        # Get source output
        source_out = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        follow_g1 = [np.log(x) for x in g1]
        follow_g2 = [np.log(x) for x in g2]

        # Get follow-up output
        follow_out = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertAlmostEqual(source_out, follow_out)

    @parameterized.expand(load_test_cases)
    def test39(self, g1: list, g2: list):
        """MR39: Sorting both groups and then adding the mean value to each element, the result should not change."""
        # Get source output
        source_out = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        follow_g1 = [x + np.mean(g1) for x in sorted(g1)]
        follow_g2 = [x + np.mean(g2) for x in sorted(g2)]

        # Get follow-up output
        follow_out = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertAlmostEqual(source_out, follow_out)

    @parameterized.expand(load_test_cases)
    def test40(self, g1: list, g2: list):
        """MR40: Replacing each element in one group with its square, the result should not change."""
        # Get source output
        source_out = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        follow_g1 = [x**2 for x in g1]

        # Get follow-up output
        follow_out = f_oneway(follow_g1, g2).pvalue

        # Verification
        self.assertAlmostEqual(source_out, follow_out)

    @parameterized.expand(load_test_cases)
    def test41(self, g1: list, g2: list):
        """MR41: Subtracting the median of each group from each element, the result should not change."""
        # Get source output
        source_out = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        median_g1 = np.median(g1)
        median_g2 = np.median(g2)
        follow_g1 = [x - median_g1 for x in g1]
        follow_g2 = [x - median_g2 for x in g2]

        # Get follow-up output
        follow_out = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertAlmostEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
