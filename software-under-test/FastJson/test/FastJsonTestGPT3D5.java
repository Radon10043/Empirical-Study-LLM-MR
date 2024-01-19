package test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.stream.Stream;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;
import com.alibaba.fastjson.JSON;
import com.alibaba.fastjson.JSONArray;
import com.alibaba.fastjson.JSONObject;

public class FastJsonTestGPT3D5 {
    /**
     * Metamorphic Relation 4: The input is an empty hash table. Converting the empty hash table
     * into a JSON string should result in an empty string.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test4(String input) {
        /* Construct source input */
        HashMap<Object, Object> source_in = new HashMap<Object, Object>();

        /* Get source output */
        String source_out = JSON.toJSONString(source_in);

        /* Verification */
        assertTrue(source_out.isEmpty());
    }

    /**
     * Metamorphic Relation 5: The input is a null object. Converting the null object into a JSON
     * string should result in null or an empty string.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test5(String input) {
        /* Construct source input */
        Object source_in = null;

        /* Get source output */
        String source_out = JSON.toJSONString(source_in);

        /* Verification */
        assertTrue(source_out == null || source_out.isEmpty());
    }

    /**
     * Metamorphic Relation 6: The input is a string representing a JSON object. Adding a new
     * key-value pair with the same key but different value should result in a different parse
     * result.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test6(String source_in) {
        /* Get source output */
        Object source_out = JSON.parseObject(source_in);

        /* Construct follow-up input */
        JSONObject jsonObject = JSON.parseObject(source_in);
        jsonObject.put("key", "new_value");
        String follow_in = jsonObject.toJSONString();

        /* Get follow-up output */
        Object follow_out = JSON.parseObject(follow_in);

        /* Verification */
        assertNotEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 7: The input is a string representing a JSON array. Reversing the order
     * of elements in the array should result in the same parse result.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void test7(String source_in) {
        /* Get source output */
        Object source_out = JSON.parseArray(source_in);

        /* Construct follow-up input */
        JSONArray jsonArray = JSON.parseArray(source_in);
        Collections.reverse(jsonArray);
        String follow_in = jsonArray.toJSONString();

        /* Get follow-up output */
        Object follow_out = JSON.parseArray(follow_in);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 8: The input is a string representing a JSON array. Adding a new element
     * to the array should result in a parse result with a larger size.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void test8(String source_in) {
        /* Get source output */
        Object source_out = JSON.parseArray(source_in);

        /* Construct follow-up input */
        JSONArray jsonArray = JSON.parseArray(source_in);
        jsonArray.add("new_element");
        String follow_in = jsonArray.toJSONString();

        /* Get follow-up output */
        Object follow_out = JSON.parseArray(follow_in);

        /* Verification */
        assertTrue(((JSONArray) follow_out).size() > ((JSONArray) source_out).size());
    }

    /**
     * Metamorphic Relation 9: The input is a string representing a JSON object. Removing a
     * key-value pair from the object should result in a smaller size parse result.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test9(String source_in) {
        /* Get source output */
        JSONObject source_out = JSON.parseObject(source_in);

        /* Construct follow-up input */
        JSONObject follow_in = JSON.parseObject(source_in);
        String keyToRemove = follow_in.keySet().iterator().next();
        follow_in.remove(keyToRemove);
        String follow_out = follow_in.toJSONString();

        /* Get follow-up output */
        JSONObject follow_out_object = JSON.parseObject(follow_out);

        /* Verification */
        assertTrue(source_out.size() > follow_out_object.size());
    }

    /**
     * Metamorphic Relation 10: The input is a string representing a JSON object. Removing quotes
     * from the keys in the JSON string should result in an equivalent parse result.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test10(String source_in) {
        /* Get source output */
        JSONObject source_out = JSON.parseObject(source_in);

        /* Construct follow-up input */
        String follow_in = source_in.replaceAll("\"(\\w+)\":", "$1:");
        String follow_out = JSON.parseObject(follow_in).toJSONString();

        /* Verification */
        assertEquals(source_out, JSON.parseObject(follow_out));
    }

    /**
     * Metamorphic Relation 11: The input is a string representing a JSON array. Replacing a subset
     * of elements with a different subset of elements having the same total length should result in
     * an equivalent parse result.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void test11(String source_in) {
        /* Get source output */
        JSONArray source_out = JSON.parseArray(source_in);

        /* Construct follow-up input */
        JSONArray follow_in = JSON.parseArray(source_in);
        // Replace a subset with the same length with a different subset
        JSONArray replacement = new JSONArray();
        for (int i = 0; i < follow_in.size() / 2; i++) {
            replacement.add("new_value" + i);
        }
        for (int i = follow_in.size() / 2; i < follow_in.size(); i++) {
            replacement.add(follow_in.get(i));
        }
        String follow_out = replacement.toJSONString();

        /* Get follow-up output */
        JSONArray follow_out_array = JSON.parseArray(follow_out);

        /* Verification */
        assertEquals(source_out, follow_out_array);
    }

    /**
     * Metamorphic Relation 12: The input is a string representing a JSON array. Reordering the
     * elements in the array should result in an equivalent parse result.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void test12(String source_in) {
        /* Get source output */
        JSONArray source_out = JSON.parseArray(source_in);

        /* Construct follow-up input */
        JSONArray follow_in = JSON.parseArray(source_in);
        Collections.shuffle(follow_in);
        String follow_out = follow_in.toJSONString();

        /* Get follow-up output */
        JSONArray follow_out_array = JSON.parseArray(follow_out);

        /* Verification */
        assertEquals(source_out, follow_out_array);
    }

    /**
     * Metamorphic Relation 13: The input is a string representing a JSON array. Annotating the
     * elements of the array with extra whitespace should result in an equivalent parse result.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void test13(String source_in) {
        /* Get source output */
        JSONArray source_out = JSON.parseArray(source_in);

        /* Construct follow-up input */
        JSONArray follow_in = JSON.parseArray(source_in);
        // Annotate each element with extra whitespace
        for (int i = 0; i < follow_in.size(); i++) {
            follow_in.set(i, "  " + follow_in.get(i) + "  ");
        }
        String follow_out = follow_in.toJSONString();

        /* Get follow-up output */
        JSONArray follow_out_array = JSON.parseArray(follow_out);

        /* Verification */
        assertEquals(source_out, follow_out_array);
    }

    /**
     * Metamorphic Relation 14: The input is a string representing a JSON array. Duplicating the
     * elements in the array should result in a larger size parse result.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void test14(String source_in) {
        /* Get source output */
        JSONArray source_out = JSON.parseArray(source_in);

        /* Construct follow-up input */
        JSONArray follow_in = JSON.parseArray(source_in);

        /* Fix by Radon */
        // Duplicate each element in the array
        int n = follow_in.size();
        for (int i = 0; i < n; i++) {
            follow_in.add(follow_in.get(i));
        }
        String follow_out = follow_in.toJSONString();

        /* Get follow-up output */
        JSONArray follow_out_array = JSON.parseArray(follow_out);

        /* Verification */
        assertTrue(follow_out_array.size() > source_out.size());
    }

    /**
     * Metamorphic Relation 15: The input is a string representing a JSON array. Replacing a subset
     * of elements with a different subset of elements should result in a different parse result.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void test15(String source_in) {
        /* Get source output */
        JSONArray source_out = JSON.parseArray(source_in);

        /* Construct follow-up input */
        JSONArray follow_in = JSON.parseArray(source_in);
        // Replace a subset with a different subset
        JSONArray replacement = new JSONArray();
        for (int i = 0; i < follow_in.size() / 2; i++) {
            replacement.add(i);
        }
        for (int i = follow_in.size() / 2; i < follow_in.size(); i++) {
            replacement.add(follow_in.get(i));
        }
        String follow_out = replacement.toJSONString();

        /* Get follow-up output */
        JSONArray follow_out_array = JSON.parseArray(follow_out);

        /* Verification */
        assertNotEquals(source_out, follow_out_array);
    }

    /**
     * Metamorphic Relation 16: The input is a string representing a JSON array. Replacing a subset
     * of elements with an empty subset should result in a different parse result.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void test16(String source_in) {
        /* Get source output */
        JSONArray source_out = JSON.parseArray(source_in);

        /* Construct follow-up input */
        JSONArray follow_in = JSON.parseArray(source_in);
        // Replace a subset with an empty subset
        for (int i = 0; i < follow_in.size() / 2; i++) {
            follow_in.set(i, null);
        }
        String follow_out = follow_in.toJSONString();

        /* Get follow-up output */
        JSONArray follow_out_array = JSON.parseArray(follow_out);

        /* Verification */
        assertNotEquals(source_out, follow_out_array);
    }

    /**
     * Metamorphic Relation 17: The input is a string representing a JSON array. Reversing the order
     * of elements and then reversing the order again should result in the original parse result.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void test17(String source_in) {
        /* Get source output */
        JSONArray source_out = JSON.parseArray(source_in);

        /* Construct follow-up input */
        JSONArray follow_in = JSON.parseArray(source_in);
        Collections.reverse(follow_in);
        Collections.reverse(follow_in); // Re-reverse to original order
        String follow_out = follow_in.toJSONString();

        /* Get follow-up output */
        JSONArray follow_out_array = JSON.parseArray(follow_out);

        /* Verification */
        assertEquals(source_out, follow_out_array);
    }

    /**
     * Metamorphic Relation 18: The input is a string representing a JSON array. Adding a null
     * element to the array should result in a larger size parse result.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void test18(String source_in) {
        /* Get source output */
        JSONArray source_out = JSON.parseArray(source_in);

        /* Construct follow-up input */
        JSONArray follow_in = JSON.parseArray(source_in);
        follow_in.add(null);
        String follow_out = follow_in.toJSONString();

        /* Get follow-up output */
        JSONArray follow_out_array = JSON.parseArray(follow_out);

        /* Verification */
        assertTrue(follow_out_array.size() > source_out.size());
    }

    /**
     * Metamorphic Relation 19: The input is a string representing a JSON array. Removing null
     * elements from the array should result in a smaller size parse result.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void test19(String source_in) {
        /* Get source output */
        JSONArray source_out = JSON.parseArray(source_in);

        /* Construct follow-up input */
        JSONArray follow_in = JSON.parseArray(source_in);
        // Remove null elements
        for (int i = 0; i < follow_in.size(); i++) {
            if (follow_in.get(i) == null) {
                follow_in.remove(i);
                i--;
            }
        }
        String follow_out = follow_in.toJSONString();

        /* Get follow-up output */
        JSONArray follow_out_array = JSON.parseArray(follow_out);

        /* Verification */
        assertTrue(follow_out_array.size() < source_out.size());
    }

    /**
     * Metamorphic Relation 20: The input is a string representing a JSON array. Replacing all
     * elements with null should result in a smaller size parse result.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void test20(String source_in) {
        /* Get source output */
        JSONArray source_out = JSON.parseArray(source_in);

        /* Construct follow-up input */
        JSONArray follow_in = new JSONArray(Collections.nCopies(source_out.size(), null));
        String follow_out = follow_in.toJSONString();

        /* Get follow-up output */
        JSONArray follow_out_array = JSON.parseArray(follow_out);

        /* Verification */
        assertTrue(follow_out_array.size() < source_out.size());
    }

    /**
     * Metamorphic Relation 21: The input is a string representing a JSON array. Adding an array as
     * an element should result in a larger size parse result.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void test21(String source_in) {
        /* Get source output */
        JSONArray source_out = JSON.parseArray(source_in);

        /* Construct follow-up input */
        JSONArray follow_in = JSON.parseArray(source_in);
        follow_in.add(new JSONArray()); // Add an empty array as an element
        String follow_out = follow_in.toJSONString();

        /* Get follow-up output */
        JSONArray follow_out_array = JSON.parseArray(follow_out);

        /* Verification */
        assertTrue(follow_out_array.size() > source_out.size());
    }

    /**
     * Metamorphic Relation 22: The input is a string representing a JSON array. Replacing all
     * elements with a duplicate subset of elements should result in an equivalent parse result.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void test22(String source_in) {
        /* Get source output */
        JSONArray source_out = JSON.parseArray(source_in);

        /* Construct follow-up input */
        JSONArray follow_in =
                new JSONArray(Collections.nCopies(source_out.size(), source_out.get(0)));

        /* Get follow-up output */
        String follow_out = follow_in.toJSONString();
        JSONArray follow_out_array = JSON.parseArray(follow_out);

        /* Verification */
        assertEquals(source_out, follow_out_array);
    }

    /**
     * Metamorphic Relation 23: The input is a string representing a JSON object. Adding a nested
     * JSON object as a value should result in a larger size parse result.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test23(String source_in) {
        /* Get source output */
        JSONObject source_out = JSON.parseObject(source_in);

        /* Construct follow-up input */
        JSONObject follow_in = JSON.parseObject(source_in);
        follow_in.put("nestedObject", new JSONObject()); // Add a nested JSON object
        String follow_out = follow_in.toJSONString();

        /* Get follow-up output */
        JSONObject follow_out_object = JSON.parseObject(follow_out);

        /* Verification */
        assertTrue(follow_out_object.size() > source_out.size());
    }

    /**
     * Metamorphic Relation 24: The input is a string representing a JSON object. Adding a nested
     * JSON array as a value should result in a larger size parse result.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test24(String source_in) {
        /* Get source output */
        JSONObject source_out = JSON.parseObject(source_in);

        /* Construct follow-up input */
        JSONObject follow_in = JSON.parseObject(source_in);
        follow_in.put("nestedArray", new JSONArray()); // Add a nested JSON array
        String follow_out = follow_in.toJSONString();

        /* Get follow-up output */
        JSONObject follow_out_object = JSON.parseObject(follow_out);

        /* Verification */
        assertTrue(follow_out_object.size() > source_out.size());
    }

    /**
     * Metamorphic Relation 25: The input is a string representing a JSON object. Adding a nested
     * JSON array as a value should result in a parse result with a larger size.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test25(String source_in) {
        /* Get source output */
        JSONObject source_out = JSON.parseObject(source_in);

        /* Construct follow-up input */
        JSONObject follow_in = JSON.parseObject(source_in);
        follow_in.put("nestedArray", new JSONArray()); // Add a nested JSON array
        String follow_out = follow_in.toJSONString();

        /* Get follow-up output */
        JSONObject follow_out_object = JSON.parseObject(follow_out);

        /* Verification */
        assertTrue(follow_out_object.toJSONString().length() > source_out.toJSONString().length());
    }

    /**
     * Metamorphic Relation 26: The input is a string representing a JSON object. Adding a nested
     * JSON object as a value of an existing key should result in a larger size parse result.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test26(String source_in) {
        /* Get source output */
        JSONObject source_out = JSON.parseObject(source_in);

        /* Construct follow-up input */
        JSONObject follow_in = JSON.parseObject(source_in);
        follow_in.put("nestedObject", new JSONObject()); // Add a nested JSON object
        String follow_out = follow_in.toJSONString();

        /* Get follow-up output */
        JSONObject follow_out_object = JSON.parseObject(follow_out);

        /* Verification */
        assertTrue(follow_out_object.size() > source_out.size());
    }

    /**
     * Metamorphic Relation 27: The input is a string representing a JSON object. Removing a field
     * from the JSON object should produce a smaller size parse result.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test27(String source_in) {
        /* Get source output */
        JSONObject source_out = JSON.parseObject(source_in);

        /* Construct follow-up input */
        JSONObject follow_in = JSON.parseObject(source_in);
        String keyToRemove = follow_in.keySet().iterator().next();
        follow_in.remove(keyToRemove);
        String follow_out = follow_in.toJSONString();

        /* Get follow-up output */
        JSONObject follow_out_object = JSON.parseObject(follow_out);

        /* Verification */
        assertTrue(follow_out_object.size() < source_out.size());
    }

    /**
     * Metamorphic Relation 28: The input is a string representing a JSON object. Duplicating all
     * fields in the JSON object should result in a larger size parse result.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test28(String source_in) {
        /* Get source output */
        JSONObject source_out = JSON.parseObject(source_in);

        /* Construct follow-up input */
        JSONObject follow_in = new JSONObject();
        for (Map.Entry<String, Object> entry : source_out.entrySet()) {
            follow_in.put(entry.getKey() + "_dup", entry.getValue());
        }
        String follow_out = follow_in.toJSONString();

        /* Get follow-up output */
        JSONObject follow_out_object = JSON.parseObject(follow_out);

        /* Verification */
        assertTrue(follow_out_object.size() > source_out.size());
    }

    /**
     * Metamorphic Relation 29: The input is a string representing a JSON object. Modifying an
     * existing field's value in the JSON object should produce an equivalent parse result.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test29(String source_in) {
        /* Get source output */
        JSONObject source_out = JSON.parseObject(source_in);

        /* Construct follow-up input */
        JSONObject follow_in = JSON.parseObject(source_in);
        String keyToModify = follow_in.keySet().iterator().next();
        follow_in.put(keyToModify, "modified_value");
        String follow_out = follow_in.toJSONString();

        /* Get follow-up output */
        JSONObject follow_out_object = JSON.parseObject(follow_out);

        /* Verification */
        assertEquals(source_out, follow_out_object);
    }

    /**
     * Metamorphic Relation 30: The input is a string representing a JSON object. Reordering the
     * fields in the JSON object should produce an equivalent parse result.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test30(String source_in) {
        /* Get source output */
        JSONObject source_out = JSON.parseObject(source_in);

        /* Construct follow-up input */
        JSONObject follow_in = new JSONObject();
        List<String> keys = new ArrayList<>(source_out.keySet());
        Collections.shuffle(keys);
        for (String key : keys) {
            follow_in.put(key, source_out.get(key));
        }
        String follow_out = follow_in.toJSONString();

        /* Get follow-up output */
        JSONObject follow_out_object = JSON.parseObject(follow_out);

        /* Verification */
        assertEquals(source_out, follow_out_object);
    }

    /**
     * Metamorphic Relation 31: The input is a string representing a JSON object. Modifying the
     * object by adding and removing identical key-value pairs one by one should result in an
     * equivalent parse result.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test31(String source_in) {
        /* Get source output */
        JSONObject source_out = JSON.parseObject(source_in);

        /* Construct follow-up input */
        JSONObject follow_in = new JSONObject(source_out); // Create a copy
        // Add and remove identical key-value pairs
        for (Map.Entry<String, Object> entry : source_out.entrySet()) {
            follow_in.put("tempKey", "tempValue");
            follow_in.remove("tempKey");
        }
        String follow_out = follow_in.toJSONString();

        /* Get follow-up output */
        JSONObject follow_out_object = JSON.parseObject(follow_out);

        /* Verification */
        assertEquals(source_out, follow_out_object);
    }

    /**
     * Metamorphic Relation 32: The input is a string representing a JSON object. Replacing all
     * field values with null should result in a different parse result.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test32(String source_in) {
        /* Get source output */
        JSONObject source_out = JSON.parseObject(source_in);

        /* Construct follow-up input */
        JSONObject follow_in = new JSONObject(source_out.size());
        for (String key : source_out.keySet()) {
            follow_in.put(key, null);
        }
        String follow_out = follow_in.toJSONString();

        /* Get follow-up output */
        JSONObject follow_out_object = JSON.parseObject(follow_out);

        /* Verification */
        assertNotEquals(source_out, follow_out_object);
    }

    /**
     * Metamorphic Relation 33: The input is a string representing a JSON object. Replacing all
     * field values with the same value should result in an equivalent parse result.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test33(String source_in) {
        /* Get source output */
        JSONObject source_out = JSON.parseObject(source_in);

        /* Construct follow-up input */
        JSONObject follow_in = new JSONObject(source_out.size());
        Object value = source_out.entrySet().iterator().next().getValue();
        for (String key : source_out.keySet()) {
            follow_in.put(key, value);
        }
        String follow_out = follow_in.toJSONString();

        /* Get follow-up output */
        JSONObject follow_out_object = JSON.parseObject(follow_out);

        /* Verification */
        assertEquals(source_out, follow_out_object);
    }

    /**
     * Metamorphic Relation 34: The input is a string representing a JSON object. Adding and
     * removing fields without changing the overall size should result in an equivalent parse
     * result.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test34(String source_in) {
        /* Get source output */
        JSONObject source_out = JSON.parseObject(source_in);

        /* Construct follow-up input */
        JSONObject follow_in = new JSONObject(source_out);
        // Add and remove fields without changing the size
        int addedFields = 0;
        for (String key : source_out.keySet()) {
            follow_in.put("addedField" + addedFields, "value");
            follow_in.remove("addedField" + addedFields);
            addedFields++;
        }
        String follow_out = follow_in.toJSONString();

        /* Get follow-up output */
        JSONObject follow_out_object = JSON.parseObject(follow_out);

        /* Verification */
        assertEquals(source_out, follow_out_object);
    }

    /**
     * Metamorphic Relation 35: The input is a string representing a JSON object. Replacing all
     * field values with a different value should result in a different parse result.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test35(String source_in) {
        /* Get source output */
        JSONObject source_out = JSON.parseObject(source_in);

        /* Construct follow-up input */
        JSONObject follow_in = new JSONObject(source_out.size());
        for (String key : source_out.keySet()) {
            follow_in.put(key, "changed_value");
        }
        String follow_out = follow_in.toJSONString();

        /* Get follow-up output */
        JSONObject follow_out_object = JSON.parseObject(follow_out);

        /* Verification */
        assertNotEquals(source_out, follow_out_object);
    }

    /**
     * Metamorphic Relation 36: The input is a string representing a JSON object. Adding and
     * removing fields while maintaining a different key-value combination should result in a
     * different parse result.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test36(String source_in) {
        /* Get source output */
        JSONObject source_out = JSON.parseObject(source_in);

        /* Construct follow-up input */
        JSONObject follow_in = new JSONObject(source_out);
        // Add and remove fields while changing the key-value combination
        int addedFields = 0;
        for (String key : source_out.keySet()) {
            follow_in.put("addedField" + addedFields, "value" + addedFields);
            follow_in.remove(key);
            addedFields++;
        }
        String follow_out = follow_in.toJSONString();

        /* Get follow-up output */
        JSONObject follow_out_object = JSON.parseObject(follow_out);

        /* Verification */
        assertNotEquals(source_out, follow_out_object);
    }

    /**
     * Metamorphic Relation 37: The input is a string representing a JSON object. Applying a
     * transformation to modify the overall structure of the object should produce a different parse
     * result.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test37(String source_in) {
        /* Get source output */
        JSONObject source_out = JSON.parseObject(source_in);

        /* Construct follow-up input */
        String follow_out = "{}"; // New empty JSON object

        /* Get follow-up output */
        JSONObject follow_out_object = JSON.parseObject(follow_out);

        /* Verification */
        assertNotEquals(source_out, follow_out_object);
    }

    /**
     * Metamorphic Relation 38: The input is a string representing a complex JSON object. Reordering
     * the keys in the JSON object should produce an equivalent parse result.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test38(String source_in) {
        /* Get source output */
        JSONObject source_out = JSON.parseObject(source_in);

        /* Construct follow-up input */
        JSONObject follow_in = new JSONObject();
        List<String> keys = new ArrayList<>(source_out.keySet());
        Collections.shuffle(keys); // Randomly reorder the keys
        for (String key : keys) {
            follow_in.put(key, source_out.get(key));
        }
        String follow_out = follow_in.toJSONString();

        /* Get follow-up output */
        JSONObject follow_out_object = JSON.parseObject(follow_out);

        /* Verification */
        assertEquals(source_out, follow_out_object);
    }

    /**
     * Metamorphic Relation 39: The input is a string representing a complex JSON object. Modifying
     * a subset of fields while preserving the overall structure should produce an equivalent parse
     * result.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test39(String source_in) {
        /* Get source output */
        JSONObject source_out = JSON.parseObject(source_in);

        /* Construct follow-up input */
        JSONObject follow_in = new JSONObject(source_out);
        // Modify a subset of fields while preserving the overall structure
        int modifyCount = 0;
        for (Map.Entry<String, Object> entry : source_out.entrySet()) {
            if (modifyCount < source_out.size() / 2) {
                follow_in.put(entry.getKey(), "modified_value");
                modifyCount++;
            }
        }
        String follow_out = follow_in.toJSONString();

        /* Get follow-up output */
        JSONObject follow_out_object = JSON.parseObject(follow_out);

        /* Verification */
        assertEquals(source_out, follow_out_object);
    }

    /**
     * Metamorphic Relation 40: The input is a string representing a complex JSON object. Applying a
     * transformation to change a subset of the values should produce a different parse result.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test40(String source_in) {
        /* Get source output */
        JSONObject source_out = JSON.parseObject(source_in);

        /* Construct follow-up input */
        JSONObject follow_in = new JSONObject(source_out);
        // Change a subset of the values
        int changeCount = 0;
        for (Map.Entry<String, Object> entry : source_out.entrySet()) {
            if (changeCount < source_out.size() / 2) {
                follow_in.put(entry.getKey(), "changed_value");
                changeCount++;
            }
        }
        String follow_out = follow_in.toJSONString();

        /* Get follow-up output */
        JSONObject follow_out_object = JSON.parseObject(follow_out);

        /* Verification */
        assertNotEquals(source_out, follow_out_object);
    }

    /**
     * Metamorphic Relation 41: The input is a string representing a complex JSON object. Removing a
     * subset of fields should produce a smaller size parse result.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test41(String source_in) {
        /* Get source output */
        JSONObject source_out = JSON.parseObject(source_in);

        /* Construct follow-up input */
        JSONObject follow_in = new JSONObject(source_out);
        // Remove a subset of fields
        int removeCount = 0;
        for (Iterator<String> it = follow_in.keySet().iterator(); it.hasNext();) {  /* Fix by Radon */
            it.next();
            it.remove();
            if (++removeCount >= source_out.size() / 2) {
                break;
            }
        }
        String follow_out = follow_in.toJSONString();

        /* Get follow-up output */
        JSONObject follow_out_object = JSON.parseObject(follow_out);

        /* Verification */
        assertTrue(follow_out_object.size() < source_out.size());
    }

    /**
     * Metamorphic Relation 42: The input is a string representing a complex JSON object. Replacing
     * a subset of fields with different fields should produce a different parse result.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test42(String source_in) {
        /* Get source output */
        JSONObject source_out = JSON.parseObject(source_in);

        /* Construct follow-up input */
        JSONObject follow_in = new JSONObject(source_out);
        // Replace a subset of fields with different fields
        int replaceCount = 0;
        for (Map.Entry<String, Object> entry : source_out.entrySet()) {
            if (replaceCount < source_out.size() / 2) {
                follow_in.put("new_field_" + replaceCount, "new_value_" + replaceCount);
                follow_in.remove(entry.getKey());
                replaceCount++;
            }
        }
        String follow_out = follow_in.toJSONString();

        /* Get follow-up output */
        JSONObject follow_out_object = JSON.parseObject(follow_out);

        /* Verification */
        assertNotEquals(source_out, follow_out_object);
    }

    /**
     * Metamorphic Relation 43: The input is a string representing a complex JSON object. Replacing
     * a subset of fields with an empty object should produce a different parse result.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test43(String source_in) {
        /* Get source output */
        JSONObject source_out = JSON.parseObject(source_in);

        /* Construct follow-up input */
        JSONObject follow_in = new JSONObject(source_out);
        // Replace a subset of fields with an empty object
        int replaceCount = 0;
        for (Map.Entry<String, Object> entry : source_out.entrySet()) {
            if (replaceCount < source_out.size() / 2) {
                follow_in.put(entry.getKey(), new JSONObject());
                replaceCount++;
            }
        }
        String follow_out = follow_in.toJSONString();

        /* Get follow-up output */
        JSONObject follow_out_object = JSON.parseObject(follow_out);

        /* Verification */
        assertNotEquals(source_out, follow_out_object);
    }

    static Stream<Arguments> testcaseProvider1() throws IOException {
        return testcaseGenerator.generate_s(1000);
    }

    static Stream<Arguments> testcaseProvider2() throws IOException {
        return testcaseGenerator.generate_s_arr(1000);
    }
}
