# Prompt

## Chat 1

Metamorphic testing is usually used to check whether the software under test satisfies specific properties. Among them, metamorphic relation is the core concept of metamorphic testing. The metamorphic relation can be considered a formal expression of the properties of the software under test and usually consists of two parts, namely the input relation and the output relation.

## Chat 2

For the function $sin(x)$, assuming there is an origin input $x1$, the corresponding origin output is $y1$, $x2$ is a follow-up input, and the corresponding follow-up output is $y2$. $x2$ is transformed from $x1$, and there is an input relation between $x2$ and $x1$: $x2=\pi-x1$, an output relation between $y1$ and $y2$: $y1=y2$. Therefore, there is a metamorphic relation $sin(x)=sin(\pi-x)$.

## Chat 3

You are an expert on metamorphic testing. Based on the above case, please identify the metamorphic relation of the `rotate` function from `scipy.ndimage`. The `rotate` function performs rotation to the input image by the specific degree. Its inputs mainly include an image to be rotated and a rotation angle, and its output  is an image which is rotated by the specific angle. Please identify the metamorphic relations of this system as much as possible and codify them as Python code. Here is an example:

```python
@parameterized.expand(load_test_cases)
def test1(self, img: np.array, angle: float):
    """Rotating the same image by N degree and N+360 degree will output the same result.

    Parameters
    ----------
    img : np.array
        Input image.
    angle : float
        Rotation angle.

    Notes
    -----
    _description_
    """
    # Get source output
    source_out = ndimage.rotate(img, angle)

    # Construct follow-up input
    follow_angle = angle + 360

    # Get follow-up output
    follow_out = ndimage.rotate(img, follow_angle)

    # Verification
    self.assertTrue(np.any(follow_out - source_out) == 0)
```

## Chat 4...n

Please identify more different metamorphic relations of this system.