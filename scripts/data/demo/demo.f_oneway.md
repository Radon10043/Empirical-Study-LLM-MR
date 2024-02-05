```python
@parameterized.expand(load_test_cases)
def test1(self, g1: list, g2: list):
    """MR1: Changing the order of the samples, the result should not change."""
    # Get source output
    source_out = f_oneway(g1, g2).pvalue

    # Construct follow-up input
    follow_g1 = np.random.permutation(g1)
    follow_g2 = np.random.permutation(g2)

    # Get follow-up output
    follow_out = f_oneway(follow_g1, follow_g2).pvalue

    # Verification
    self.assertAlmostEqual(source_out, follow_out)
```