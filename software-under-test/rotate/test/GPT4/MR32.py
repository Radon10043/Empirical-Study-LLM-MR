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
    def test_rotate_different_axes(self, img: np.array, angle: float):
        """Metamorphic Relation 32: Rotating around different axes pairs by the same angle should not result in the same image for non-symmetrical images."""
        axis_pairs = [(0, 1), (0, 2), (1, 2)]
        rotated_images = []

        for axes in axis_pairs:
            # Rotate the image around each axes pair
            rotated_img = ndimage.rotate(img, angle, axes=axes, reshape=False)
            rotated_images.append(rotated_img)

        # Verification: The rotated images should not be the same
        for i in range(len(rotated_images) - 1):
            with self.assertRaises(AssertionError):
                np.testing.assert_array_equal(rotated_images[i], rotated_images[i + 1])


if __name__ == "__main__":
    unittest.main()
