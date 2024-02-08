#include <algorithm>
#include <cmath>
#include <gtest/gtest.h>
#include <vector>

#include "../src/function.h"
#include "utils.h"

using namespace std;

#define SKIP_CRASH

class BSearchParamTest : public ::testing::TestWithParam<BSearch2Input> {};

vector<int> prime_nums = {
    2,    3,    5,    7,    11,   13,   17,   19,   23,   29,   31,   37,   41,   43,   47,   53,   59,   61,   67,   71,   73,   79,   83,   89,   97,   101,
    103,  107,  109,  113,  127,  131,  137,  139,  149,  151,  157,  163,  167,  173,  179,  181,  191,  193,  197,  199,  211,  223,  227,  229,  233,  239,
    241,  251,  257,  263,  269,  271,  277,  281,  283,  293,  307,  311,  313,  317,  331,  337,  347,  349,  353,  359,  367,  373,  379,  383,  389,  397,
    401,  409,  419,  421,  431,  433,  439,  443,  449,  457,  461,  463,  467,  479,  487,  491,  499,  503,  509,  521,  523,  541,  547,  557,  563,  569,
    571,  577,  587,  593,  599,  601,  607,  613,  617,  619,  631,  641,  643,  647,  653,  659,  661,  673,  677,  683,  691,  701,  709,  719,  727,  733,
    739,  743,  751,  757,  761,  769,  773,  787,  797,  809,  811,  821,  823,  827,  829,  839,  853,  857,  859,  863,  877,  881,  883,  887,  907,  911,
    919,  929,  937,  941,  947,  953,  967,  971,  977,  983,  991,  997,  1009, 1013, 1019, 1021, 1031, 1033, 1039, 1049, 1051, 1061, 1063, 1069, 1087, 1091,
    1093, 1097, 1103, 1109, 1117, 1123, 1129, 1151, 1153, 1163, 1171, 1181, 1187, 1193, 1201, 1213, 1217, 1223, 1229, 1231, 1237, 1249, 1259, 1277, 1279, 1283,
    1289, 1291, 1297, 1301, 1303, 1307, 1319, 1321, 1327, 1361, 1367, 1373, 1381, 1399, 1409, 1423, 1427, 1429, 1433, 1439, 1447, 1451, 1453, 1459, 1471, 1481,
    1483, 1487, 1489, 1493, 1499, 1511, 1523, 1531, 1543, 1549, 1553, 1559, 1567, 1571, 1579, 1583, 1597, 1601, 1607, 1609, 1613, 1619, 1621, 1627, 1637, 1657,
    1663, 1667, 1669, 1693, 1697, 1699, 1709, 1721, 1723, 1733, 1741, 1747, 1753, 1759, 1777, 1783, 1787, 1789, 1801, 1811, 1823, 1831, 1847, 1861, 1867, 1871,
    1873, 1877, 1879, 1889, 1901, 1907, 1913, 1931, 1933, 1949, 1951, 1973, 1979, 1987, 1993, 1997, 1999, 2003, 2011, 2017, 2027, 2029, 2039, 2053, 2063, 2069,
    2081, 2083, 2087, 2089, 2099, 2111, 2113, 2129, 2131, 2137, 2141, 2143, 2153, 2161, 2179, 2203, 2207, 2213, 2221, 2237, 2239, 2243, 2251, 2267, 2269, 2273,
    2281, 2287, 2293, 2297, 2309, 2311, 2333, 2339, 2341, 2347, 2351, 2357, 2371, 2377, 2381, 2383, 2389, 2393, 2399, 2411, 2417, 2423, 2437, 2441, 2447, 2459,
    2467, 2473, 2477, 2503, 2521, 2531, 2539, 2543, 2549, 2551, 2557, 2579, 2591, 2593, 2609, 2617, 2621, 2633, 2647, 2657, 2659, 2663, 2671, 2677, 2683, 2687,
    2689, 2693, 2699, 2707, 2711, 2713, 2719, 2729, 2731, 2741, 2749, 2753, 2767, 2777, 2789, 2791, 2797, 2801, 2803, 2819, 2833, 2837, 2843, 2851, 2857, 2861,
    2879, 2887, 2897, 2903, 2909, 2917, 2927, 2939, 2953, 2957, 2963, 2969, 2971, 2999, 3001, 3011, 3019, 3023, 3037, 3041, 3049, 3061, 3067, 3079, 3083, 3089,
    3109, 3119, 3121, 3137, 3163, 3167, 3169, 3181, 3187, 3191, 3203, 3209, 3217, 3221, 3229, 3251, 3253, 3257, 3259, 3271, 3299, 3301, 3307, 3313, 3319, 3323,
    3329, 3331, 3343, 3347, 3359, 3361, 3371, 3373, 3389, 3391, 3407, 3413, 3433, 3449, 3457, 3461, 3463, 3467, 3469, 3491, 3499, 3511, 3517, 3527, 3529, 3533,
    3539, 3541, 3547, 3557, 3559, 3571, 3581, 3583, 3593, 3607, 3613, 3617, 3623, 3631, 3637, 3643, 3659, 3671, 3673, 3677, 3691, 3697, 3701, 3709, 3719, 3727,
    3733, 3739, 3761, 3767, 3769, 3779, 3793, 3797, 3803, 3821, 3823, 3833, 3847, 3851, 3853, 3863, 3877, 3881, 3889, 3907, 3911, 3917, 3919, 3923, 3929, 3931,
    3943, 3947, 3967, 3989, 4001, 4003, 4007, 4013, 4019, 4021, 4027, 4049, 4051, 4057, 4073, 4079, 4091, 4093, 4099, 4111, 4127, 4129, 4133, 4139, 4153, 4157,
    4159, 4177, 4201, 4211, 4217, 4219, 4229, 4231, 4241, 4243, 4253, 4259, 4261, 4271, 4273, 4283, 4289, 4297, 4327, 4337, 4339, 4349, 4357, 4363, 4373, 4391,
    4397, 4409, 4421, 4423, 4441, 4447, 4451, 4457, 4463, 4481, 4483, 4493, 4507, 4513, 4517, 4519, 4523, 4547, 4549, 4561, 4567, 4583, 4591, 4597, 4603, 4621,
    4637, 4639, 4643, 4649, 4651, 4657, 4663, 4673, 4679, 4691, 4703, 4721, 4723, 4729, 4733, 4751, 4759, 4783, 4787, 4789, 4793, 4799, 4801, 4813, 4817, 4831,
    4861, 4871, 4877, 4889, 4903, 4909, 4919, 4931, 4933, 4937, 4943, 4951, 4957, 4967, 4969, 4973, 4987, 4993, 4999, 5003, 5009, 5011, 5021, 5023, 5039, 5051,
    5059, 5077, 5081, 5087, 5099, 5101, 5107, 5113, 5119, 5147, 5153, 5167, 5171, 5179, 5189, 5197, 5209, 5227, 5231, 5233, 5237, 5261, 5273, 5279, 5281, 5297,
    5303, 5309, 5323, 5333, 5347, 5351, 5381, 5387, 5393, 5399, 5407, 5413, 5417, 5419, 5431, 5437, 5441, 5443, 5449, 5471, 5477, 5479, 5483, 5501, 5503, 5507,
    5519, 5521, 5527, 5531, 5557, 5563, 5569, 5573, 5581, 5591, 5623, 5639, 5641, 5647, 5651, 5653, 5657, 5659, 5669, 5683, 5689, 5693, 5701, 5711, 5717, 5737,
    5741, 5743, 5749, 5779, 5783, 5791, 5801, 5807, 5813, 5821, 5827, 5839, 5843, 5849, 5851, 5857, 5861, 5867, 5869, 5879, 5881, 5897, 5903, 5923, 5927, 5939,
    5953, 5981, 5987, 6007, 6011, 6029, 6037, 6043, 6047, 6053, 6067, 6073, 6079, 6089, 6091, 6101, 6113, 6121, 6131, 6133, 6143, 6151, 6163, 6173, 6197, 6199,
    6203, 6211, 6217, 6221, 6229, 6247, 6257, 6263, 6269, 6271, 6277, 6287, 6299, 6301, 6311, 6317, 6323, 6329, 6337, 6343, 6353, 6359, 6361, 6367, 6373, 6379,
    6389, 6397, 6421, 6427, 6449, 6451, 6469, 6473, 6481, 6491, 6521, 6529, 6547, 6551, 6553, 6563, 6569, 6571, 6577, 6581, 6599, 6607, 6619, 6637, 6653, 6659,
    6661, 6673, 6679, 6689, 6691, 6701, 6703, 6709, 6719, 6733, 6737, 6761, 6763, 6779, 6781, 6791, 6793, 6803, 6823, 6827, 6829, 6833, 6841, 6857, 6863, 6869,
    6871, 6883, 6899, 6907, 6911, 6917, 6947, 6949, 6959, 6961, 6967, 6971, 6977, 6983, 6991, 6997, 7001, 7013, 7019, 7027, 7039, 7043, 7057, 7069, 7079, 7103,
    7109, 7121, 7127, 7129, 7151, 7159, 7177, 7187, 7193, 7207, 7211, 7213, 7219, 7229, 7237, 7243, 7247, 7253, 7283, 7297, 7307, 7309, 7321, 7331, 7333, 7349,
    7351, 7369, 7393, 7411, 7417, 7433, 7451, 7457, 7459, 7477, 7481, 7487, 7489, 7499, 7507, 7517, 7523, 7529, 7537, 7541, 7547, 7549, 7559, 7561, 7573, 7577,
    7583, 7589, 7591, 7603, 7607, 7621, 7639, 7643, 7649, 7669, 7673, 7681, 7687, 7691, 7699, 7703, 7717, 7723, 7727, 7741, 7753, 7757, 7759, 7789, 7793, 7817,
    7823, 7829, 7841, 7853, 7867, 7873, 7877, 7879, 7883, 7901, 7907, 7919, 7927, 7933, 7937, 7949, 7951, 7963, 7993, 8009, 8011, 8017, 8039, 8053, 8059, 8069,
    8081, 8087, 8089, 8093, 8101, 8111, 8117, 8123, 8147, 8161, 8167, 8171, 8179, 8191, 8209, 8219, 8221, 8231, 8233, 8237, 8243, 8263, 8269, 8273, 8287, 8291,
    8293, 8297, 8311, 8317, 8329, 8353, 8363, 8369, 8377, 8387, 8389, 8419, 8423, 8429, 8431, 8443, 8447, 8461, 8467, 8501, 8513, 8521, 8527, 8537, 8539, 8543,
    8563, 8573, 8581, 8597, 8599, 8609, 8623, 8627, 8629, 8641, 8647, 8663, 8669, 8677, 8681, 8689, 8693, 8699, 8707, 8713, 8719, 8731, 8737, 8741, 8747, 8753,
    8761, 8779, 8783, 8803, 8807, 8819, 8821, 8831, 8837, 8839, 8849, 8861, 8863, 8867, 8887, 8893, 8923, 8929, 8933, 8941, 8951, 8963, 8969, 8971, 8999, 9001,
    9007, 9011, 9013, 9029, 9041, 9043, 9049, 9059, 9067, 9091, 9103, 9109, 9127, 9133, 9137, 9151, 9157, 9161, 9173, 9181, 9187, 9199, 9203, 9209, 9221, 9227,
    9239, 9241, 9257, 9277, 9281, 9283, 9293, 9311, 9319, 9323, 9337, 9341, 9343, 9349, 9371, 9377, 9391, 9397, 9403, 9413, 9419, 9421, 9431, 9433, 9437, 9439,
    9461, 9463, 9467, 9473, 9479, 9491, 9497, 9511, 9521, 9533, 9539, 9547, 9551, 9587, 9601, 9613, 9619, 9623, 9629, 9631, 9643, 9649, 9661, 9677, 9679, 9689,
    9697, 9719, 9721, 9733, 9739, 9743, 9749, 9767, 9769, 9781, 9787, 9791, 9803, 9811, 9817, 9829, 9833, 9839, 9851, 9857, 9859, 9871, 9883, 9887, 9901, 9907,
    9923, 9929, 9931, 9941, 9949, 9967, 9973};

/**
 * @brief Metamorphic relation 1: The result should be the same when searching for the complement of the target value.
 *
 */
TEST_P(BSearchParamTest, MR1) {
    GTEST_FAIL();
    // /* Get source input */
    // BSearch2Input input = GetParam();
    // vector<int> vec = input.vec;
    // int target = input.target;

    // /* Get source output */
    // int source_out = bin_search(vec, target);

    // /* Construct follow-up input*/
    // int complement_target = find_complement(target, vec); // function to find complement of target value
    // vector<int> follow_vec = vec;

    // /* Get follow-up output */
    // int follow_out = bin_search(follow_vec, complement_target);

    // /* Verification */
    // EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 2: The result should be the same when searching for the same target value in the reverse order of the vector.
 *
 */
TEST_P(BSearchParamTest, MR2) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input*/
    reverse(vec.begin(), vec.end()); // reverse the vector
    int follow_target = target;

    /* Get follow-up output */
    int follow_out = bin_search(vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 3: The result should be the same when searching for the same target value in a vector with all elements multiplied by a constant
 * value.
 *
 */
TEST_P(BSearchParamTest, MR3) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input*/
    int constant = 2;
    vector<int> follow_vec = vec;
    for (int &val : follow_vec)
        val *= constant;
    int follow_target = target * constant;

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 4: The result should be the same when searching for a target value in a vector with additional elements greater than the target
 * value appended at the end.
 *
 */
TEST_P(BSearchParamTest, MR4) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input*/
    vector<int> follow_vec = vec;
    int append_count = 3;
    for (int i = 0; i < append_count; i++) {
        follow_vec.push_back(target + i + 1);
    }
    int follow_target = target;

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 5: The result should be the same when searching for the same target value in a sub-vector of the original vector.
 *
 */
TEST_P(BSearchParamTest, MR5) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input*/
    int start_index = vec.size() / 3;   // start index of sub-vector
    int end_index = vec.size() * 2 / 3; // end index of sub-vector
    vector<int> follow_vec(vec.begin() + start_index, vec.begin() + end_index);
    int follow_target = target;

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 6: The result should be the same when searching for the same target value in a vector with all elements incremented by a constant
 * value.
 *
 */
TEST_P(BSearchParamTest, MR6) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input*/
    int constant = 5;
    vector<int> follow_vec = vec;
    for (int &val : follow_vec)
        val += constant;
    int follow_target = target + constant;

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 7: The result should be the same when searching for the same target value in a vector with elements rearranged in a random order.
 *
 */
TEST_P(BSearchParamTest, MR7) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input*/
    vector<int> follow_vec = vec;
    random_shuffle(follow_vec.begin(), follow_vec.end()); // rearrange the vector
    int follow_target = target;

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 8: The result should be the same when searching for the same target value in a vector with the first half of the elements
 * repeated twice.
 *
 */
TEST_P(BSearchParamTest, MR8) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input*/
    vector<int> follow_vec = vec;
    follow_vec.insert(follow_vec.end(), vec.begin(), vec.begin() + vec.size() / 2); // repeat the first half of the vector
    int follow_target = target;

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 9: The result should be the same when searching for the same target value in a vector with one occurrence of the target value
 * replaced by a different value.
 *
 */
TEST_P(BSearchParamTest, MR9) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input*/
    vector<int> follow_vec = vec;
    int replace_index = find(follow_vec.begin(), follow_vec.end(), target) - follow_vec.begin(); // function to find the index of target value
    follow_vec[replace_index] = target + 1; // replace one occurrence of target value with a different value
    int follow_target = target;

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 10: The result should be the same when searching for the same target value in a vector with all elements multiplied by -1.
 *
 */
TEST_P(BSearchParamTest, MR10) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    for (int &val : follow_vec)
        val *= -1;
    int follow_target = -target;

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 11: The result should be the same when searching for the same target value in a vector that includes the original vector followed
 * by the original vector in reverse order.
 *
 */
TEST_P(BSearchParamTest, MR11) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    for (int i = vec.size() - 1; i >= 0; i--)
        follow_vec.push_back(vec[i]);
    int follow_target = target;

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 12: The result should be the same when searching for the same target value in a vector with the even-indexed elements doubled.
 *
 */
TEST_P(BSearchParamTest, MR12) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    for (int i = 0; i < vec.size(); i += 2) {
        vec[i] *= 2;
    }
    int follow_target = target;

    /* Get follow-up output */
    int follow_out = bin_search(vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 13: The result should be the same when searching for the same target value in a vector with the elements sorted in descending
 * order.
 *
 */
TEST_P(BSearchParamTest, MR13) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    sort(vec.rbegin(), vec.rend()); // sort the vector in descending order
    int follow_target = target;

    /* Get follow-up output */
    int follow_out = bin_search(vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 14: The result should be the same when searching for the same target value in a vector with all elements shifted one position to
 * the right, and the last element moved to the beginning.
 *
 */
TEST_P(BSearchParamTest, MR14) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    rotate(vec.rbegin(), vec.rbegin() + 1, vec.rend()); // shift elements to the right and move the last element to the beginning
    int follow_target = target;

    /* Get follow-up output */
    int follow_out = bin_search(vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 15: The result should be the same when searching for the same target value in a vector with the elements shifted in a circular
 * manner to the right.
 *
 */
TEST_P(BSearchParamTest, MR15) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;
    size_t n = vec.size();

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    reverse(vec.begin(), vec.end());
    reverse(vec.begin(), vec.begin() + (n % 2 == 0 ? n / 2 : n / 2 + 1));
    reverse(vec.begin() + (n % 2 == 0 ? n / 2 : n / 2 + 1), vec.end());
    reverse(vec.begin(), vec.end()); // shift elements in a circular manner to the right
    int follow_target = target;

    /* Get follow-up output */
    int follow_out = bin_search(vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 16: The result should be the same when searching for the same target value in a vector with all elements squared.
 *
 */
TEST_P(BSearchParamTest, MR16) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    for (int &val : vec) {
        val *= val; // square all elements in the vector
    }
    int follow_target = target * target; // square the target value

    /* Get follow-up output */
    int follow_out = bin_search(vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 17: The result should be the same when searching for the same target value in a vector with all elements replaced by their
 * absolute values.
 *
 */
TEST_P(BSearchParamTest, MR17) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    for (int &val : vec) {
        val = abs(val); // replace all elements with their absolute values
    }
    int follow_target = abs(target); // get the absolute value of the target

    /* Get follow-up output */
    int follow_out = bin_search(vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 18: The result should be the same when searching for the same target value in a vector with elements flipped (reversed) and then
 * sorted in ascending order.
 *
 */
TEST_P(BSearchParamTest, MR18) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    reverse(vec.begin(), vec.end()); // reverse the vector
    sort(vec.begin(), vec.end());    // sort the vector in ascending order
    int follow_target = target;

    /* Get follow-up output */
    int follow_out = bin_search(vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 19: The result should be the same when searching for the same target value in a vector that contains the original elements with
 * all duplicates removed.
 *
 */
TEST_P(BSearchParamTest, MR19) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    sort(vec.begin(), vec.end());                                      // sort the vector
    vec.resize(distance(vec.begin(), unique(vec.begin(), vec.end()))); // remove duplicates
    int follow_target = target;

    /* Get follow-up output */
    int follow_out = bin_search(vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 20: The result should be the same when searching for the same target value in a vector with one occurrence of the target value
 * removed.
 *
 */
TEST_P(BSearchParamTest, MR20) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    vector<int>::iterator it = find(vec.begin(), vec.end(), target);
    if (it != vec.end()) {
        vec.erase(it); // remove one occurrence of the target value
    }
    int follow_target = target;

    /* Get follow-up output */
    int follow_out = bin_search(vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 21: The result should be the same when searching for the same target value in a vector with one occurrence of the target value
 * repeated one more time.
 *
 */
TEST_P(BSearchParamTest, MR21) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    vec.push_back(target); // add one more occurrence of the target value
    int follow_target = target;

    /* Get follow-up output */
    int follow_out = bin_search(vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 22: The result should be the same when searching for the same target value in a vector with elements replaced by their
 * corresponding indices.
 *
 */
TEST_P(BSearchParamTest, MR22) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    for (int i = 0; i < vec.size(); ++i) {
        vec[i] = i; // replace elements with their indices
    }
    int follow_target = distance(vec.begin(), find(vec.begin(), vec.end(), target)); // set the follow-up target as the index of the original target

    /* Get follow-up output */
    int follow_out = bin_search(vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 23: The result should be the same when searching for the same target value in a vector with the elements multiplied by a scaling
 * factor and then rounded to the nearest integer.
 *
 */
TEST_P(BSearchParamTest, MR23) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    float scaling_factor = 2.5;
    for (int &val : vec) {
        val = round(val * scaling_factor); // multiply elements by scaling factor and round to nearest integer
    }
    int follow_target = round(target * scaling_factor); // set the follow-up target as the original target multiplied by the scaling factor and rounded

    /* Get follow-up output */
    int follow_out = bin_search(vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 24: The result should be the same when searching for the same target value in a vector with the elements replaced by their
 * logarithms to the base 2.
 *
 */
TEST_P(BSearchParamTest, MR24) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* Construct follow-up input */
    for (int &val : vec) {
        if (val > 0) {
            val = log2(val); // replace elements with their logarithms to the base 2
        }
    }
    int follow_target = log2(target); // set the follow-up target as the logarithm of the original target to the base 2

    /* Get follow-up output */
    bool follow_out = bin_search(vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 25: The result should be the same when searching for the same target value in a vector with the elements doubled, and the target
 * value doubled.
 *
 */
TEST_P(BSearchParamTest, MR25) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* Construct follow-up input */
    for (int &val : vec) {
        val *= 2; // double all elements in the vector
    }
    int follow_target = target * 2; // double the target value

    /* Get follow-up output */
    bool follow_out = bin_search(vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 26: The result should be the same when searching for the same target value in a vector with all elements divided by a fixed
 * divisor.
 *
 */
TEST_P(BSearchParamTest, MR26) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* Construct follow-up input */
    int divisor = 3;
    for (int &val : vec) {
        val /= divisor; // divide all elements in the vector by a fixed divisor
    }
    int follow_target = target / divisor; // divide the target value by the same divisor

    /* Get follow-up output */
    bool follow_out = bin_search(vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 27: The result should be the same when searching for the same target value in a vector with only the odd elements shifted to the
 * left.
 *
 */
TEST_P(BSearchParamTest, MR27) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* Construct follow-up input */
    for (int &val : vec) {
        if (val % 2 != 0) {
            val = val << 1; // shift left all odd elements in the vector
        }
    }
    int follow_target = target << 1; // shift left the target value

    /* Get follow-up output */
    bool follow_out = bin_search(vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 28: The result should be the same when searching for the same target value in a vector with each element replaced by the square
 * root of their absolute value.
 *
 */
TEST_P(BSearchParamTest, MR28) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* Construct follow-up input */
    for (int &val : vec) {
        val = sqrt(abs(val)); // replace each element by the square root of their absolute value
    }
    int follow_target = sqrt(abs(target)); // set the target value as the square root of its absolute value

    /* Get follow-up output */
    bool follow_out = bin_search(vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 29: The result should be the same when searching for the same target value in a vector with elements raised to the power of 3.
 *
 */
TEST_P(BSearchParamTest, MR29) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* Construct follow-up input */
    for (int &val : vec) {
        val = pow(val, 3); // raise each element to the power of 3
    }
    int follow_target = pow(target, 3); // raise the target value to the power of 3

    /* Get follow-up output */
    bool follow_out = bin_search(vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

int productOfPrimeFactors(int value) {
    int res = 1;
    for (auto &prime : prime_nums) {
        if (value % prime == 0) {
            res = prime;
            break;
        }
    }
    return res;
}

/**
 * @brief Metamorphic relation 30: The result should be the same when searching for the same target value in a vector with prime factors of each element instead
 * of the original values.
 *
 */
TEST_P(BSearchParamTest, MR30) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* Construct follow-up input */
    for (int &val : vec) {
        val = productOfPrimeFactors(val); // replace each element by the product of its prime factors
    }
    int follow_target = productOfPrimeFactors(target); // set the target value as the product of its prime factors

    /* Get follow-up output */
    bool follow_out = bin_search(vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 31: The result should be the same when searching for the same target value in a vector with all elements converted to their
 * binary representation.
 *
 */
TEST_P(BSearchParamTest, MR31) {
    GTEST_FAIL();
    // /* Get source input */
    // BSearch2Input input = GetParam();
    // vector<int> vec = input.vec;
    // int target = input.target;

    // /* Get source output */
    // bool source_out = bin_search(vec, target);

    // /* Construct follow-up input */
    // for (int &val : vec) {
    //     val = binaryRepresentation(val); // convert each element to its binary representation
    // }
    // int follow_target = binaryRepresentation(target); // set the target value as its binary representation

    // /* Get follow-up output */
    // bool follow_out = bin_search(vec, follow_target);

    // /* Verification */
    // EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 32: The result should be the same when searching for the same target value in a vector with all elements mapped to their ASCII
 * values.
 *
 */
TEST_P(BSearchParamTest, MR32) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* Construct follow-up input */
    for (int &val : vec) {
        val = char(val); // map each element to its ASCII value
    }
    int follow_target = char(target); // set the target value as its ASCII value

    /* Get follow-up output */
    bool follow_out = bin_search(vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 33: The result should be the same when searching for the same target value in a vector with all elements replaced by their
 * absolute differences from the target value.
 *
 */
TEST_P(BSearchParamTest, MR33) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* Construct follow-up input */
    for (int &val : vec) {
        val = abs(val - target); // replace each element by its absolute difference from the target value
    }
    int follow_target = 0; // set the target value as zero

    /* Get follow-up output */
    bool follow_out = bin_search(vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 34: The result should be the same when searching for the same target value in a vector where each element represents the
 * cumulative sum up to that element.
 *
 */
TEST_P(BSearchParamTest, MR34) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* Construct follow-up input */
    for (int i = 1; i < vec.size(); ++i) {
        vec[i] += vec[i - 1]; // replace each element by the cumulative sum up to that element
    }
    int follow_target = target + vec[0]; // set the target value as its original value plus the first element of the vector

    /* Get follow-up output */
    bool follow_out = bin_search(vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 35: The result should be the same when searching for the same target value in a vector where each element represents the
 * difference between consecutive elements.
 *
 */
TEST_P(BSearchParamTest, MR35) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* Construct follow-up input */
    vector<int> diffVec;
    for (int i = 1; i < vec.size(); ++i) {
        diffVec.push_back(vec[i] - vec[i - 1]); // replace each element by the difference between consecutive elements
    }
    int follow_target = target - vec[0]; // set the target value as its original value minus the first element of the vector

    /* Get follow-up output */
    bool follow_out = bin_search(diffVec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 36: The result should be the same when searching for the same target value in a vector with elements replaced by their fractional
 * parts.
 *
 */
TEST_P(BSearchParamTest, MR36) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* Construct follow-up input */
    for (int i = 0; i < vec.size(); ++i) {
        vec[i] = vec[i] - static_cast<int>(vec[i]); // replace each element by its fractional part
    }
    int follow_target = target - static_cast<int>(target); // set the target value as its fractional part

    /* Get follow-up output */
    bool follow_out = bin_search(vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 37: The result should be the same when searching for the same target value in a vector that is the result of applying a linear
 * transformation to the original vector.
 *
 */
TEST_P(BSearchParamTest, MR37) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;
    float a = 1.5, b = 2.0; // constants for linear transformation

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* Construct follow-up input */
    for (int i = 0; i < vec.size(); ++i) {
        vec[i] = a * vec[i] + b; // linear transformation
    }
    int follow_target = static_cast<int>(a * target + b); // linear transformation of the target value

    /* Get follow-up output */
    bool follow_out = bin_search(vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 38: The result should be the same when searching for the target value in a vector formed by repeating the original vector twice.
 *
 */
TEST_P(BSearchParamTest, MR38) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* Construct follow-up input */
    vector<int> follow_vec;
    follow_vec.insert(follow_vec.end(), vec.begin(), vec.end());
    follow_vec.insert(follow_vec.end(), vec.begin(), vec.end());

    /* Get follow-up output */
    bool follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 39: The result should be the same when searching for the target value in a vector with elements randomly shuffled.
 *
 */
TEST_P(BSearchParamTest, MR39) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* Construct follow-up input */
    random_shuffle(vec.begin(), vec.end()); // shuffle the elements randomly

    /* Get follow-up output */
    bool follow_out = bin_search(vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 40: The result should be the same when searching for the target value in a vector where all elements are incremented followed by
 * appending the original vector.
 */
TEST_P(BSearchParamTest, MR40) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* Construct follow-up input */
    int inc = 5;
    for (int &val : vec) {
        val += inc; // increment all elements
    }
    vector<int> follow_vec = vec;
    follow_vec.insert(follow_vec.end(), vec.begin(), vec.end()); // append the original vector

    /* Get follow-up output */
    bool follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 41: The result should be the same when searching for the target value in a vector containing the original vector with all
 * duplicates removed.
 */
TEST_P(BSearchParamTest, MR41) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* Construct follow-up input */
    sort(vec.begin(), vec.end());
    vec.erase(unique(vec.begin(), vec.end()), vec.end()); // remove duplicates

    /* Get follow-up output */
    bool follow_out = bin_search(vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 42: The result should be the same when searching for the target value in a vector sorted in descending order.
 */
TEST_P(BSearchParamTest, MR42) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* Construct follow-up input */
    sort(vec.rbegin(), vec.rend()); // sort the vector in descending order

    /* Get follow-up output */
    bool follow_out = bin_search(vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 43: The result should be the same when searching for the target value in a vector with all elements negated.
 */
TEST_P(BSearchParamTest, MR43) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* Construct follow-up input */
    for (int &val : vec) {
        val = -val; // negate all elements
    }

    /* Get follow-up output */
    bool follow_out = bin_search(vec, -target); // negate the target value

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 44: The result should be the same when searching for the target value in a vector consisting of the original vector with one
 * occurrence of the target value appended at the end.
 */
TEST_P(BSearchParamTest, MR44) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    follow_vec.push_back(target); // append one occurrence of the target value

    /* Get follow-up output */
    bool follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 45: The result should be the same when searching for the target value in a vector with each element replaced by the sum of itself
 * and the target value.
 */
TEST_P(BSearchParamTest, MR45) {
    /* Get source input */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    bool source_out = bin_search(vec, target);

    /* Construct follow-up input */
    for (int &val : vec) {
        val += target; // add the target value to each element
    }

    /* Get follow-up output */
    bool follow_out = bin_search(vec, target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

INSTANTIATE_TEST_CASE_P(TrueReturn, BSearchParamTest, testing::ValuesIn(get_tcs_randomly()));