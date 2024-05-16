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
    def test_rotate_image_center(self, img: np.array, angle: float):
        """Metamorphic Relation 21: Rotating a centered sub-image and the full image should yield identical center regions if reshape=False."""
        # Assuming the images are square for simplicity, get the centered sub-image
        center_region_size = img.shape[0] // 2
        half_center = center_region_size // 2
        sub_img = img[half_center:-half_center, half_center:-half_center]

        # Rotate the centered sub-image
        rotated_sub_img = ndimage.rotate(sub_img, angle, reshape=False)

        # Rotate the full image
        rotated_full_img = ndimage.rotate(img, angle, reshape=False)

        # Verification: The center of the full rotated image should be identical to the rotated sub-image
        center_of_rotated_full = rotated_full_img[half_center:-half_center, half_center:-half_center]
        np.testing.assert_array_almost_equal(rotated_sub_img, center_of_rotated_full)


if __name__ == "__main__":
    unittest.main()
