from utils import *


class TestingClass(unittest.TestCase):
    # Fix by Radon
    @parameterized.expand(load_test_cases)
    def test14(self, img: np.array, angle: float):
        """Metamorphic Relation 14: Rotating the image by angle A and then performing a Fourier transform is equivalent to performing a Fourier transform on the original image and then rotating the result by angle A."""
        # Get source output
        source_out = ndimage.rotate(img, angle)

        # Construct follow-up input
        follow_out = np.fft.fft2(source_out)

        # Verification
        fft_source_out = np.fft.fft2(img)
        rotated_fft_out = ndimage.rotate(fft_source_out, angle)
        self.assertTrue(np.array_equal(follow_out, rotated_fft_out))


if __name__ == "__main__":
    unittest.main()
