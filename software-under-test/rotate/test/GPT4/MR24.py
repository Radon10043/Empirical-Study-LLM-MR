import os
import sys
import unittest

import numpy as np
from scipy import ndimage, datasets
from parameterized import parameterized

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))

from utils import gen_tcs_randomly


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test_rotate_then_mirror(self, img: np.array, angle: float):
        """Metamorphic Relation 24: Rotating an image and then mirroring should produce the same result as first mirroring and then rotating in the opposite direction."""
        axis = np.random.choice(img.ndim)  # Pick a random axis to mirror

        # Rotate then mirror
        rotated_img = ndimage.rotate(img, angle, reshape=False)
        mirrored_after_rotate = np.flip(rotated_img, axis)

        # Mirror then rotate in the opposite direction
        mirrored_img = np.flip(img, axis)
        rotated_after_mirror = ndimage.rotate(mirrored_img, -angle, reshape=False)

        # Verification
        np.testing.assert_array_almost_equal(mirrored_after_rotate, rotated_after_mirror)


if __name__ == "__main__":
    unittest.main()
