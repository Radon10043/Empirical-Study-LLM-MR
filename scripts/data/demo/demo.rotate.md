```python
@parameterized.expand(load_test_cases)
def test1(self, img: np.array, angle: float):
    """Metamorphic Relation 1: Rotating the same image by N degree and N+360 degree will output the same result."""
    # Get source output
    source_out = ndimage.rotate(img, angle)

    # Construct follow-up input
    follow_angle = angle + 360

    # Get follow-up output
    follow_out = ndimage.rotate(img, follow_angle)

    # Verification
    self.assertTrue(np.any(follow_out - source_out) == 0)
```