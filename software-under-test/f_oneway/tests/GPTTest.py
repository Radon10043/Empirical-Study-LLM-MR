"""
Author: Radon
Date: 2023-12-05 15:20:27
LastEditors: Radon
LastEditTime: 2023-12-05 16:19:50
Description: Hi, say something
"""
from scipy.stats import f_oneway
from parameterized import parameterized

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
    # fmt:off
    test_cases = [
        ([1, 2, 3, 4, 5], [2, 3, 4, 5, 6]),
        ([1, 3, 5, 7, 9], [1, 3, 5, 7, 9])
    ]
    # fmt:on
    return test_cases


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test_order_invariance(self, g1, g2):
        """MR1: Changing the order of the samples, the result should not change."""
        # Get original output
        origin_res = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        follow_g1 = np.random.permutation(g1)
        follow_g2 = np.random.permutation(g2)

        # Get follow-up output
        follow_res = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertEqual(origin_res, follow_res)

    @parameterized.expand(load_test_cases)
    def test_constant_addition(self, g1, g2):
        """MR2: Adding a constant to all values in a group should not change the result."""
        # Get original output
        origin_res = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        constant = np.random.uniform(0, 10)
        follow_g1 = g1 + constant
        follow_g2 = g2 + constant

        # Get follow-up output
        follow_res = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertEqual(origin_res, follow_res)

    @parameterized.expand(load_test_cases)
    def test_scaling(self, g1, g2):
        """MR3: Scaling all values in a group by a constant factor should not change the result."""
        # Get original output
        origin_res = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        scale_factor = np.random.uniform(0.1, 2)
        follow_g1 = g1 * scale_factor
        follow_g2 = g2 * scale_factor

        # Get follow-up output
        follow_res = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertEqual(origin_res, follow_res)

    @parameterized.expand(load_test_cases)
    def test_group_permutation(self, g1, g2):
        """MR4: Permuting the group labels should not change the result."""
        # Get original output
        origin_res = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        follow_g1 = g2  # Swap group labels
        follow_g2 = g1

        # Get follow-up output
        follow_res = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertEqual(origin_res, follow_res)

    @parameterized.expand(load_test_cases)
    def test_sample_permutation_within_group(self, g1, g2):
        """MR5: Permuting the samples within each group should not change the result."""
        # Get original output
        origin_res = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        follow_g1 = np.random.permutation(g1)
        follow_g2 = np.random.permutation(g2)

        # Get follow-up output
        follow_res = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertEqual(origin_res, follow_res)

    @parameterized.expand(load_test_cases)
    def test_group_mean_preservation(self, g1, g2):
        """MR6: Adding or subtracting a constant to all values in a group should not change the result."""
        # Get original output
        origin_res = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        constant = np.random.uniform(0, 10)
        follow_g1 = g1 + constant
        follow_g2 = g2 - constant

        # Get follow-up output
        follow_res = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertEqual(origin_res, follow_res)

    @parameterized.expand(load_test_cases)
    def test_group_mean_equality(self, g1, g2):
        """MR7: If the means of two groups are equal, the p-value should be close to 1."""
        # Get original output
        origin_res = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        follow_g1 = np.random.normal(loc=5, scale=1, size=len(g1))  # Create a new group with the same mean
        follow_g2 = np.random.normal(loc=5, scale=1, size=len(g2))

        # Get follow-up output
        follow_res = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertAlmostEqual(origin_res, follow_res, places=3)  # Check if p-value is close to 1

    @parameterized.expand(load_test_cases)
    def test_group_mean_inequality(self, g1, g2):
        """MR8: If the means of two groups are unequal, the p-value should be less than 0.05."""
        # Get original output
        origin_res = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        follow_g1 = g1 + np.random.normal(loc=2, scale=1, size=len(g1))  # Increase mean of one group
        follow_g2 = g2 + np.random.normal(loc=2, scale=1, size=len(g2))

        # Get follow-up output
        follow_res = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertLess(origin_res, 0.05)  # Original p-value should be less than 0.05
        self.assertLess(follow_res, 0.05)  # Follow-up p-value should also be less than 0.05

    @parameterized.expand(load_test_cases)
    def test_group_variance_equality(self, g1, g2):
        """MR9: If the variances of two groups are equal, the p-value should be close to 1."""
        # Get original output
        origin_res = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        follow_g1 = np.random.normal(loc=5, scale=1, size=len(g1))  # Create a new group with similar variance
        follow_g2 = np.random.normal(loc=5, scale=1, size=len(g2))

        # Get follow-up output
        follow_res = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertAlmostEqual(origin_res, follow_res, places=3)  # Check if p-value is close to 1

    @parameterized.expand(load_test_cases)
    def test_data_repetition(self, g1, g2):
        """MR10: Repeating the data within each group should not change the result."""
        # Get original output
        origin_res = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        follow_g1 = np.tile(g1, 2)  # Repeat each element in g1 twice
        follow_g2 = np.tile(g2, 2)  # Repeat each element in g2 twice

        # Get follow-up output
        follow_res = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertEqual(origin_res, follow_res)

    @parameterized.expand(load_test_cases)
    def test_outlier_addition(self, g1, g2):
        """MR11: Adding outliers to one group should not significantly change the result."""
        # Get original output
        origin_res = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        outlier_g1 = np.append(g1, [100, 150])  # Add outliers to g1
        follow_g2 = g2

        # Get follow-up output
        follow_res = f_oneway(outlier_g1, follow_g2).pvalue

        # Verification
        self.assertGreaterEqual(origin_res, follow_res)

    @parameterized.expand(load_test_cases)
    def test_subset_selection(self, g1, g2):
        """MR12: Selecting a subset of data from each group should not change the result."""
        # Get original output
        origin_res = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        subset_g1 = np.random.choice(g1, size=len(g1) // 2, replace=False)  # Select half of the data from g1
        subset_g2 = np.random.choice(g2, size=len(g2) // 2, replace=False)  # Select half of the data from g2

        # Get follow-up output
        follow_res = f_oneway(subset_g1, subset_g2).pvalue

        # Verification
        self.assertEqual(origin_res, follow_res)

    @parameterized.expand(load_test_cases)
    def test_data_scaling(self, g1, g2):
        """MR13: Scaling all data within each group by a constant factor should not change the result."""
        # Get original output
        origin_res = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        scale_factor = np.random.uniform(0.5, 2)
        follow_g1 = g1 * scale_factor
        follow_g2 = g2 * scale_factor

        # Get follow-up output
        follow_res = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertEqual(origin_res, follow_res)

    @parameterized.expand(load_test_cases)
    def test_data_shuffling(self, g1, g2):
        """MR14: Shuffling the data across both groups should not change the result."""
        # Get original output
        origin_res = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        all_data = np.concatenate([g1, g2])
        np.random.shuffle(all_data)
        follow_g1 = all_data[: len(g1)]
        follow_g2 = all_data[len(g1) :]

        # Get follow-up output
        follow_res = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertEqual(origin_res, follow_res)

    @parameterized.expand(load_test_cases)
    def test_data_replacement(self, g1, g2):
        """MR15: Randomly replacing a subset of data within each group should not change the result."""
        # Get original output
        origin_res = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        replace_indices_g1 = np.random.choice(len(g1), size=len(g1) // 2, replace=False)
        replace_indices_g2 = np.random.choice(len(g2), size=len(g2) // 2, replace=False)
        follow_g1 = np.copy(g1)
        follow_g2 = np.copy(g2)

        # Replace data in both groups
        follow_g1[replace_indices_g1] = np.random.uniform(0, 10, size=len(replace_indices_g1))
        follow_g2[replace_indices_g2] = np.random.uniform(0, 10, size=len(replace_indices_g2))

        # Get follow-up output
        follow_res = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertEqual(origin_res, follow_res)

    @parameterized.expand(load_test_cases)
    def test_group_size_invariance(self, g1, g2):
        """MR16: Adding or removing data points from a group should not significantly change the result."""
        # Get original output
        origin_res = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        g1_subset = g1[: len(g1) // 2]  # Take a subset of data from group 1
        follow_g1 = np.concatenate([g1_subset, np.random.normal(loc=5, scale=1, size=len(g1) // 2)])  # Add new data points to group 1
        follow_g2 = g2

        # Get follow-up output
        follow_res = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertGreaterEqual(origin_res, follow_res)

    @parameterized.expand(load_test_cases)
    def test_data_transformation(self, g1, g2):
        """MR17: Applying a monotonic transformation to the data within each group should not change the result."""
        # Get original output
        origin_res = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        follow_g1 = np.sin(g1)  # Apply a monotonic transformation to group 1
        follow_g2 = np.sin(g2)

        # Get follow-up output
        follow_res = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertEqual(origin_res, follow_res)

    @parameterized.expand(load_test_cases)
    def test_data_combination(self, g1, g2):
        """MR18: Combining two groups into a single group should not change the result."""
        # Get original output
        origin_res = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        combined_data = np.concatenate([g1, g2])  # Combine both groups into a single group
        follow_g1 = combined_data
        follow_g2 = np.array([])  # Empty group

        # Get follow-up output
        follow_res = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertEqual(origin_res, follow_res)

    @parameterized.expand(load_test_cases)
    def test_subgroup_creation(self, g1, g2):
        """MR19: Creating subgroups within each group should not change the result."""
        # Get original output
        origin_res = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        subgroup_size = len(g1) // 2
        follow_g1 = [np.random.choice(g1, size=subgroup_size, replace=False) for _ in range(2)]  # Create subgroups in group 1
        follow_g1 = np.concatenate(follow_g1)
        follow_g2 = [np.random.choice(g2, size=subgroup_size, replace=False) for _ in range(2)]  # Create subgroups in group 2
        follow_g2 = np.concatenate(follow_g2)

        # Get follow-up output
        follow_res = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertEqual(origin_res, follow_res)

    @parameterized.expand(load_test_cases)
    def test_data_reordering_within_group(self, g1, g2):
        """MR20: Reordering data within each group should not change the result."""
        # Get original output
        origin_res = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        follow_g1 = np.random.permutation(g1)  # Reorder data in group 1
        follow_g2 = np.random.permutation(g2)  # Reorder data in group 2

        # Get follow-up output
        follow_res = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertEqual(origin_res, follow_res)

    @parameterized.expand(load_test_cases)
    def test_data_scaling_between_groups(self, g1, g2):
        """MR21: Scaling one group more than the other should change the result."""
        # Get original output
        origin_res = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        follow_g1 = g1 * 2  # Scale group 1 more than group 2
        follow_g2 = g2

        # Get follow-up output
        follow_res = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertNotEqual(origin_res, follow_res)

    @parameterized.expand(load_test_cases)
    def test_data_outliers(self, g1, g2):
        """MR22: Introducing outliers to one group should affect the result."""
        # Get original output
        origin_res = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        outlier_g1 = np.append(g1, [100, 150])  # Add outliers to g1
        follow_g2 = g2

        # Get follow-up output
        follow_res = f_oneway(outlier_g1, follow_g2).pvalue

        # Verification
        self.assertNotEqual(origin_res, follow_res)

    @parameterized.expand(load_test_cases)
    def test_group_data_distribution(self, g1, g2):
        """MR23: Changing the distribution of data within a group should affect the result."""
        # Get original output
        origin_res = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        follow_g1 = np.random.exponential(scale=1, size=len(g1))  # Change distribution of data in group 1
        follow_g2 = g2

        # Get follow-up output
        follow_res = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertNotEqual(origin_res, follow_res)

    @parameterized.expand(load_test_cases)
    def test_data_independent_samples(self, g1, g2):
        """MR24: Creating two independent samples with the same distribution should not affect the result."""
        # Get original output
        origin_res = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        follow_g1 = np.random.normal(loc=5, scale=1, size=len(g1))  # Independent sample with similar distribution
        follow_g2 = np.random.normal(loc=5, scale=1, size=len(g2))

        # Get follow-up output
        follow_res = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertEqual(origin_res, follow_res)

    @parameterized.expand(load_test_cases)
    def test_group_data_variance(self, g1, g2):
        """MR25: Changing the variance of data within a group should affect the result."""
        # Get original output
        origin_res = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        follow_g1 = np.random.normal(loc=5, scale=2, size=len(g1))  # Change variance of data in group 1
        follow_g2 = g2

        # Get follow-up output
        follow_res = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertNotEqual(origin_res, follow_res)

    @parameterized.expand(load_test_cases)
    def test_data_distribution_shift(self, g1, g2):
        """MR26: Shifting the distribution of data within a group should affect the result."""
        # Get original output
        origin_res = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        follow_g1 = g1 + 5  # Shift distribution of data in group 1
        follow_g2 = g2

        # Get follow-up output
        follow_res = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertNotEqual(origin_res, follow_res)

    @parameterized.expand(load_test_cases)
    def test_data_symmetry(self, g1, g2):
        """MR27: Creating a symmetric distribution for one group should not significantly change the result."""
        # Get original output
        origin_res = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        follow_g1 = np.concatenate([g1, -g1])  # Create a symmetric distribution for group 1
        follow_g2 = g2

        # Get follow-up output
        follow_res = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertAlmostEqual(origin_res, follow_res, places=2)  # Check if p-value is close

    @parameterized.expand(load_test_cases)
    def test_data_clustering(self, g1, g2):
        """MR28: Clustering data within each group should not significantly change the result."""
        # Get original output
        origin_res = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        cluster_center = np.mean(g1)  # Use the mean as a cluster center
        follow_g1 = np.random.normal(loc=cluster_center, scale=1, size=len(g1))  # Cluster data around the center
        follow_g2 = g2

        # Get follow-up output
        follow_res = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertAlmostEqual(origin_res, follow_res, places=2)  # Check if p-value is close

    @parameterized.expand(load_test_cases)
    def test_data_mixture(self, g1, g2):
        """MR29: Creating a mixture of distributions for one group should affect the result."""
        # Get original output
        origin_res = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        follow_g1 = np.concatenate([np.random.normal(loc=5, scale=1, size=len(g1) // 2), np.random.normal(loc=10, scale=2, size=len(g1) // 2)])  # Mixture of distributions for group 1
        follow_g2 = g2

        # Get follow-up output
        follow_res = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertNotEqual(origin_res, follow_res)

    @parameterized.expand(load_test_cases)
    def test_data_constant_group(self, g1, g2):
        """MR30: Assigning a constant value to all data in one group should affect the result."""
        # Get original output
        origin_res = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        follow_g1 = np.full_like(g1, fill_value=5)  # Assign a constant value to all data in group 1
        follow_g2 = g2

        # Get follow-up output
        follow_res = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertNotEqual(origin_res, follow_res)

    @parameterized.expand(load_test_cases)
    def test_data_interleaving(self, g1, g2):
        """MR31: Interleaving data between groups should not change the result."""
        # Get original output
        origin_res = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        interleaved_data = np.concatenate([g1, g2])  # Interleave data between groups
        follow_g1 = interleaved_data[: len(g1)]
        follow_g2 = interleaved_data[len(g1) :]

        # Get follow-up output
        follow_res = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertEqual(origin_res, follow_res)

    @parameterized.expand(load_test_cases)
    def test_data_expansion(self, g1, g2):
        """MR32: Expanding data within each group should not change the result."""
        # Get original output
        origin_res = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        expanded_g1 = np.repeat(g1, 2)  # Expand data in group 1
        expanded_g2 = np.repeat(g2, 2)  # Expand data in group 2

        # Get follow-up output
        follow_res = f_oneway(expanded_g1, expanded_g2).pvalue

        # Verification
        self.assertEqual(origin_res, follow_res)

    @parameterized.expand(load_test_cases)
    def test_data_replacement_between_groups(self, g1, g2):
        """MR33: Randomly replacing a subset of data between groups should not change the result."""
        # Get original output
        origin_res = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        replace_indices_g1 = np.random.choice(len(g1), size=len(g1) // 2, replace=False)
        replace_indices_g2 = np.random.choice(len(g2), size=len(g2) // 2, replace=False)
        follow_g1 = np.copy(g1)
        follow_g2 = np.copy(g2)

        # Replace data between groups
        follow_g1[replace_indices_g1] = np.random.uniform(0, 10, size=len(replace_indices_g1))
        follow_g2[replace_indices_g2] = np.random.uniform(0, 10, size=len(replace_indices_g2))

        # Get follow-up output
        follow_res = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertEqual(origin_res, follow_res)

    @parameterized.expand(load_test_cases)
    def test_data_sampling(self, g1, g2):
        """MR34: Randomly sampling data from each group should not change the result."""
        # Get original output
        origin_res = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        sample_size = min(len(g1), len(g2)) // 2
        follow_g1 = np.random.choice(g1, size=sample_size, replace=False)  # Randomly sample data from group 1
        follow_g2 = np.random.choice(g2, size=sample_size, replace=False)  # Randomly sample data from group 2

        # Get follow-up output
        follow_res = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertEqual(origin_res, follow_res)

    @parameterized.expand(load_test_cases)
    def test_data_outliers_removal(self, g1, g2):
        """MR35: Removing outliers from each group should not change the result."""
        # Get original output
        origin_res = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        follow_g1 = g1[g1 < np.percentile(g1, 95)]  # Remove outliers from group 1
        follow_g2 = g2[g2 < np.percentile(g2, 95)]  # Remove outliers from group 2

        # Get follow-up output
        follow_res = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertEqual(origin_res, follow_res)

    @parameterized.expand(load_test_cases)
    def test_data_shift_within_group(self, g1, g2):
        """MR36: Shifting data within each group should not change the result."""
        # Get original output
        origin_res = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        follow_g1 = g1 + 2  # Shift data within group 1
        follow_g2 = g2

        # Get follow-up output
        follow_res = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertEqual(origin_res, follow_res)

    @parameterized.expand(load_test_cases)
    def test_data_transformation_within_group(self, g1, g2):
        """MR37: Applying a monotonic transformation to data within each group should not change the result."""
        # Get original output
        origin_res = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        follow_g1 = np.exp(g1)  # Apply a monotonic transformation to data in group 1
        follow_g2 = np.exp(g2)  # Apply a monotonic transformation to data in group 2

        # Get follow-up output
        follow_res = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertEqual(origin_res, follow_res)

    @parameterized.expand(load_test_cases)
    def test_data_partitioning(self, g1, g2):
        """MR38: Partitioning the data within each group into subgroups should not change the result."""
        # Get original output
        origin_res = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        partition_size = len(g1) // 2
        follow_g1 = [g1[:partition_size], g1[partition_size:]]  # Partition data in group 1
        follow_g1 = np.concatenate(follow_g1)
        follow_g2 = [g2[:partition_size], g2[partition_size:]]  # Partition data in group 2
        follow_g2 = np.concatenate(follow_g2)

        # Get follow-up output
        follow_res = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertEqual(origin_res, follow_res)

    @parameterized.expand(load_test_cases)
    def test_data_scaling_within_group(self, g1, g2):
        """MR39: Scaling data within each group by a constant factor should not change the result."""
        # Get original output
        origin_res = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        scale_factor = 2
        follow_g1 = g1 * scale_factor  # Scale data in group 1
        follow_g2 = g2 * scale_factor  # Scale data in group 2

        # Get follow-up output
        follow_res = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertEqual(origin_res, follow_res)

    @parameterized.expand(load_test_cases)
    def test_group_data_distribution_shift(self, g1, g2):
        """MR40: Shifting the distribution of data within a group should affect the result."""
        # Get original output
        origin_res = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        follow_g1 = g1 + np.random.normal(loc=2, scale=1, size=len(g1))  # Shift distribution of data in group 1
        follow_g2 = g2

        # Get follow-up output
        follow_res = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertNotEqual(origin_res, follow_res)

    @parameterized.expand(load_test_cases)
    def test_data_symmetry_shift(self, g1, g2):
        """MR41: Shifting a symmetric distribution within a group should affect the result."""
        # Get original output
        origin_res = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        follow_g1 = np.concatenate([g1 + 2, -g1 + 2])  # Shift symmetric distribution in group 1
        follow_g2 = g2

        # Get follow-up output
        follow_res = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertNotEqual(origin_res, follow_res)

    @parameterized.expand(load_test_cases)
    def test_data_scaling_within_group_and_between_groups(self, g1, g2):
        """MR42: Scaling data within each group and between groups should not change the result."""
        # Get original output
        origin_res = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        scale_factor_within_group = 2
        scale_factor_between_groups = 0.5
        follow_g1 = g1 * scale_factor_within_group  # Scale data within group 1
        follow_g2 = g2 * scale_factor_within_group  # Scale data within group 2
        follow_g1 = follow_g1 * scale_factor_between_groups  # Scale data between groups

        # Get follow-up output
        follow_res = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertEqual(origin_res, follow_res)

    @parameterized.expand(load_test_cases)
    def test_data_subsetting(self, g1, g2):
        """MR43: Subsetting data within each group should not change the result."""
        # Get original output
        origin_res = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        subset_size = len(g1) // 2
        follow_g1 = np.random.choice(g1, size=subset_size, replace=False)  # Randomly subset data from group 1
        follow_g2 = np.random.choice(g2, size=subset_size, replace=False)  # Randomly subset data from group 2

        # Get follow-up output
        follow_res = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertEqual(origin_res, follow_res)

    @parameterized.expand(load_test_cases)
    def test_data_merging(self, g1, g2):
        """MR44: Merging data from multiple sources within each group should not change the result."""
        # Get original output
        origin_res = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        merged_data_g1 = np.concatenate([g1, np.random.normal(loc=10, scale=2, size=len(g1) // 2)])  # Merge data in group 1
        merged_data_g2 = np.concatenate([g2, np.random.normal(loc=5, scale=1, size=len(g2) // 2)])  # Merge data in group 2

        # Get follow-up output
        follow_res = f_oneway(merged_data_g1, merged_data_g2).pvalue

        # Verification
        self.assertEqual(origin_res, follow_res)

    @parameterized.expand(load_test_cases)
    def test_data_mismatched_sizes(self, g1, g2):
        """MR45: Using groups with mismatched sizes should not change the result."""
        # Get original output
        origin_res = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        follow_g1 = g1[:-1]  # Remove one data point from group 1
        follow_g2 = g2

        # Get follow-up output
        follow_res = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertEqual(origin_res, follow_res)

    @parameterized.expand(load_test_cases)
    def test_data_sampling_with_replacement(self, g1, g2):
        """MR46: Randomly sampling data from each group with replacement should not change the result."""
        # Get original output
        origin_res = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        sample_size = min(len(g1), len(g2)) // 2
        follow_g1 = np.random.choice(g1, size=sample_size, replace=True)  # Randomly sample data from group 1 with replacement
        follow_g2 = np.random.choice(g2, size=sample_size, replace=True)  # Randomly sample data from group 2 with replacement

        # Get follow-up output
        follow_res = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertEqual(origin_res, follow_res)

    @parameterized.expand(load_test_cases)
    def test_data_group_combination(self, g1, g2):
        """MR47: Combining data from both groups and then splitting them into two groups should not change the result."""
        # Get original output
        origin_res = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        combined_data = np.concatenate([g1, g2])  # Combine data from both groups
        np.random.shuffle(combined_data)  # Shuffle the combined data
        follow_g1 = combined_data[: len(g1)]  # Split the shuffled data into group 1
        follow_g2 = combined_data[len(g1) :]  # Split the shuffled data into group 2

        # Get follow-up output
        follow_res = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertEqual(origin_res, follow_res)

    @parameterized.expand(load_test_cases)
    def test_data_group_intersection(self, g1, g2):
        """MR48: Taking the intersection of data between groups should not change the result."""
        # Get original output
        origin_res = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        intersection_data = np.intersect1d(g1, g2)  # Take the intersection of data between groups
        follow_g1 = intersection_data[intersection_data.searchsorted(g1)]  # Retain only intersecting data in group 1
        follow_g2 = intersection_data[intersection_data.searchsorted(g2)]  # Retain only intersecting data in group 2

        # Get follow-up output
        follow_res = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertEqual(origin_res, follow_res)

    @parameterized.expand(load_test_cases)
    def test_data_permutation_within_group(self, g1, g2):
        """MR49: Permuting the order of data within each group should not change the result."""
        # Get original output
        origin_res = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        permuted_g1 = np.random.permutation(g1)  # Permute the order of data in group 1
        permuted_g2 = np.random.permutation(g2)  # Permute the order of data in group 2

        # Get follow-up output
        follow_res = f_oneway(permuted_g1, permuted_g2).pvalue

        # Verification
        self.assertEqual(origin_res, follow_res)

    @parameterized.expand(load_test_cases)
    def test_data_subset_within_group(self, g1, g2):
        """MR50: Considering a subset of data within each group should not change the result."""
        # Get original output
        origin_res = f_oneway(g1, g2).pvalue

        # Construct follow-up input
        subset_size = len(g1) // 2
        follow_g1 = g1[:subset_size]  # Take a subset of data from group 1
        follow_g2 = g2[:subset_size]  # Take a subset of data from group 2

        # Get follow-up output
        follow_res = f_oneway(follow_g1, follow_g2).pvalue

        # Verification
        self.assertEqual(origin_res, follow_res)


def test():
    g1 = [1,2,3,4,5]
    g2 = [2,3,4,5,6]
    ori = f_oneway(g1, g2).pvalue

    for i in range(5):
        g1[i] *= 2
        g2[i] *= 2

    fol = f_oneway(g1, g2).pvalue

    print(ori == fol)


if __name__ == "__main__":
    # test()
    unittest.main()
