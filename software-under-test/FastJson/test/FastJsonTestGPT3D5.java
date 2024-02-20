package test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.TreeMap;
import java.util.stream.Collectors;
import java.util.stream.Stream;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;
import com.alibaba.fastjson.JSON;
import com.alibaba.fastjson.JSONArray;
import com.alibaba.fastjson.JSONObject;
import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.google.gson.JsonParser;
import com.google.gson.JsonElement;

public class FastJsonTestGPT3D5 {
    /**
     * Metamorphic Relation 1: The input is a JSON string representing an array of objects. After removing an element
     * from the array and converting it into a JSON string, the length of the follow-up JSON string is less than or equal
     * to the original JSON string.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void test1(String source_in) {
        /* Get source output */
        JSONArray sourceArray = JSON.parseArray(source_in);
        int sourceLength = sourceArray.size();
        sourceArray.remove(0);
        String source_out = sourceArray.toJSONString();

        /* Construct follow-up input */
        JSONArray followArray = JSON.parseArray(source_in);
        followArray.remove(0);

        /* Get follow-up output */
        String follow_out = followArray.toJSONString();

        /* Verification */
        assertTrue(follow_out.length() <= source_out.length());
    }

    /**
     * Metamorphic Relation 2: The input is a JSON string representing an object. Adding a new field to the object and
     * converting it into a JSON string, the length of the follow-up JSON string should be greater than or equal to the
     * original JSON string.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test2(String source_in) {
        /* Get source output */
        JSONObject sourceObj = JSON.parseObject(source_in);
        String source_out = sourceObj.toJSONString();

        /* Construct follow-up input */
        JSONObject followObj = JSON.parseObject(source_in);
        followObj.put("newField", "newValue");

        /* Get follow-up output */
        String follow_out = followObj.toJSONString();

        /* Verification */
        assertTrue(follow_out.length() >= source_out.length());
    }

    /**
     * Metamorphic Relation 3: The input is a JSON string representing an object. Removing a field from the object and
     * converting it into a JSON string, the length of the follow-up JSON string should be less than or equal to the
     * original JSON string.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test3(String source_in) {
        /* Get source output */
        JSONObject sourceObj = JSON.parseObject(source_in);
        String source_out = sourceObj.toJSONString();

        /* Construct follow-up input */
        JSONObject followObj = JSON.parseObject(source_in);
        followObj.remove("existingField");

        /* Get follow-up output */
        String follow_out = followObj.toJSONString();

        /* Verification */
        assertTrue(follow_out.length() <= source_out.length());
    }

    /**
     * Metamorphic Relation 4: The input is a JSON string representing an array of objects. Reordering the elements of the
     * array and converting it into a JSON string, the length of the follow-up JSON string is the same as the original JSON
     * string.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void test4(String source_in) {
        /* Get source output */
        JSONArray sourceArray = JSON.parseArray(source_in);
        String source_out = sourceArray.toJSONString();

        /* Construct follow-up input */
        JSONArray followArray = JSON.parseArray(source_in);
        Collections.shuffle(followArray);

        /* Get follow-up output */
        String follow_out = followArray.toJSONString();

        /* Verification */
        assertEquals(source_out.length(), follow_out.length());
    }

    /**
     * Metamorphic Relation 5: The input is a JSON string representing an object. Filtering the object to contain only selected
     * fields and converting it into a JSON string, the length of the follow-up JSON string should be less than or equal to the
     * original JSON string.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test5(String source_in) {
        /* Get source output */
        JSONObject sourceObj = JSON.parseObject(source_in);
        String source_out = sourceObj.toJSONString();

        /* Construct follow-up input */
        JSONObject followObj = JSON.parseObject(source_in);
        for (String key : new ArrayList<>(followObj.keySet())) {
            if (!key.equals("field1")) {
                followObj.remove(key);
            }
        }

        /* Get follow-up output */
        String follow_out = followObj.toJSONString();

        /* Verification */
        assertTrue(follow_out.length() <= source_out.length());
    }

    /**
     * Metamorphic Relation 6: The input is a JSON string representing a complex object. Modifying a nested field of the
     * object and converting it into a JSON string, the nested field in the follow-up JSON string should have the modified
     * value.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test6(String source_in) {
        /* Get source output */
        JSONObject sourceObj = JSON.parseObject(source_in);
        String nestedValue = sourceObj.getJSONObject("nestedObj").getString("nestedField");
        String source_out = nestedValue;

        /* Construct follow-up input */
        JSONObject followObj = JSON.parseObject(source_in);
        followObj.getJSONObject("nestedObj").put("nestedField", "modifiedValue");

        /* Get follow-up output */
        String follow_out = followObj.getJSONObject("nestedObj").getString("nestedField");

        /* Verification */
        assertEquals("modifiedValue", follow_out);
    }

    /**
     * Metamorphic Relation 7: The input is a JSON string representing an array of objects. Reversing the order of elements in
     * the array and converting it into a JSON string, the length of the follow-up JSON string is the same as the original JSON
     * string.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void test7(String source_in) {
        /* Get source output */
        JSONArray sourceArray = JSON.parseArray(source_in);
        String source_out = sourceArray.toJSONString();

        /* Construct follow-up input */
        JSONArray followArray = JSON.parseArray(source_in);
        Collections.reverse(followArray);

        /* Get follow-up output */
        String follow_out = followArray.toJSONString();

        /* Verification */
        assertEquals(source_out.length(), follow_out.length());
    }

    /**
     * Metamorphic Relation 8: The input is a JSON string representing an object. Modifying the values of all fields in the
     * object and converting it into a JSON string, the length of the follow-up JSON string is the same as the original JSON
     * string.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test8(String source_in) {
        /* Get source output */
        JSONObject sourceObj = JSON.parseObject(source_in);
        String source_out = sourceObj.toJSONString();

        /* Construct follow-up input */
        JSONObject followObj = JSON.parseObject(source_in);
        for (String key : followObj.keySet()) {
            followObj.put(key, "modifiedValue");
        }

        /* Get follow-up output */
        String follow_out = followObj.toJSONString();

        /* Verification */
        assertEquals(source_out.length(), follow_out.length());
    }

    /**
     * Metamorphic Relation 9: The input is a JSON object. Converting the JSON object into a string s1,
     * and then converting s1 back into an object, then converting the object back into a string s2.
     * The length of s1 should be the same as s2.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test9(String source_in) {   // Fixed
        JSONObject jsonobj = JSON.parseObject(source_in);

        /* Get source output */
        String s1 = jsonobj.toJSONString();
        Object object = JSON.parse(s1);

        /* Construct follow-up input */
        String s2 = JSON.toJSONString(object);

        /* Verification */
        assertEquals(s1.length(), s2.length());
    }

    /**
     * Metamorphic Relation 10: The input is a JSON string representing an object. Adding a new nested object to the original object
     * and converting it into a JSON string, the length of the follow-up JSON string should be greater than or equal to the original
     * JSON string.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test10(String source_in) {
        /* Get source output */
        JSONObject sourceObj = JSON.parseObject(source_in);
        String source_out = sourceObj.toJSONString();

        /* Construct follow-up input */
        JSONObject followObj = JSON.parseObject(source_in);
        followObj.put("newNestedObj", new JSONObject());

        /* Get follow-up output */
        String follow_out = followObj.toJSONString();

        /* Verification */
        assertTrue(follow_out.length() >= source_out.length());
    }

    /**
     * Metamorphic Relation 11: The input is a JSON string representing an array of objects. Repeating the elements of the array
     * and converting it into a JSON string, the length of the follow-up JSON string is greater than or equal to the original JSON
     * string.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void test11(String source_in) {
        /* Get source output */
        JSONArray sourceArray = JSON.parseArray(source_in);
        String source_out = sourceArray.toJSONString();

        /* Construct follow-up input */
        JSONArray followArray = JSON.parseArray(source_in);
        followArray.addAll(sourceArray.subList(0, sourceArray.size()));

        /* Get follow-up output */
        String follow_out = followArray.toJSONString();

        /* Verification */
        assertTrue(follow_out.length() >= source_out.length());
    }

    /**
     * Metamorphic Relation 12: The input is a JSON string representing an object. Removing the nested objects from the original
     * object and converting it into a JSON string, the length of the follow-up JSON string should be less than or equal to the
     * original JSON string.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test12(String source_in) {
        /* Get source output */
        JSONObject sourceObj = JSON.parseObject(source_in);
        String source_out = sourceObj.toJSONString();

        /* Construct follow-up input */
        JSONObject followObj = JSON.parseObject(source_in);
        followObj.remove("nestedObj1");
        followObj.remove("nestedObj2");

        /* Get follow-up output */
        String follow_out = followObj.toJSONString();

        /* Verification */
        assertTrue(follow_out.length() <= source_out.length());
    }

    /**
     * Metamorphic Relation 13: The input is a JSON string representing an object. Converting the JSON object into a string s1,
     * after removing all the whitespace from s1 and converting it back into an object, the resulting object should have the
     * same content as the original object.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test13(String source_in) {
        /* Get source output */
        JSONObject sourceObj = JSON.parseObject(source_in);
        String s1 = sourceObj.toJSONString();

        /* Construct follow-up input */
        String s2 = s1.replaceAll("\\s", "");
        JSONObject followObj = JSON.parseObject(s2);

        /* Verification */
        assertEquals(sourceObj, followObj);
    }

    /**
     * Metamorphic Relation 14: The input is a JSON string representing an array of objects. Replacing all the occurrences of a
     * certain value in the array with a new value and converting it into a JSON string, the length of the follow-up JSON string
     * should be the same as the original JSON string.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void test14(String source_in) {
        /* Get source output */
        JSONArray sourceArray = JSON.parseArray(source_in);
        String source_out = sourceArray.toJSONString();

        /* Construct follow-up input */
        JSONArray followArray = JSON.parseArray(source_in);
        for (int i = 0; i < followArray.size(); i++) {
            if (followArray.getString(i).equals("oldValue")) {
                followArray.set(i, "newValue");
            }
        }

        /* Get follow-up output */
        String follow_out = followArray.toJSONString();

        /* Verification */
        assertEquals(source_out.length(), follow_out.length());
    }

    /**
     * Metamorphic Relation 15: The input is a JSON string representing an object. Applying a transformation function to all the
     * field values of the object and converting it into a JSON string, the length of the follow-up JSON string should be the same
     * as the original JSON string.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test15(String source_in) {
        /* Get source output */
        JSONObject sourceObj = JSON.parseObject(source_in);
        String source_out = sourceObj.toJSONString();

        /* Construct follow-up input */
        JSONObject followObj = JSON.parseObject(source_in);
        followObj.replaceAll((key, value) -> "modifiedValue");

        /* Get follow-up output */
        String follow_out = followObj.toJSONString();

        /* Verification */
        assertEquals(source_out.length(), follow_out.length());
    }

    /**
     * Metamorphic Relation 16: The input is a JSON string representing an array of objects. Replacing a subset of the elements in
     * the array with a new set of elements and converting it into a JSON string, the length of the follow-up JSON string should be
     * the same as the original JSON string.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void test16(String source_in) {
        /* Get source output */
        JSONArray sourceArray = JSON.parseArray(source_in);
        String source_out = sourceArray.toJSONString();

        /* Construct follow-up input */
        JSONArray followArray = JSON.parseArray(source_in);
        followArray.set(0, "newElement1");
        followArray.set(2, "newElement2");

        /* Get follow-up output */
        String follow_out = followArray.toJSONString();

        /* Verification */
        assertEquals(source_out.length(), follow_out.length());
    }

    /**
     * Metamorphic Relation 17: The input is a JSON string representing an object. Performing sorting of the fields in the object
     * and converting it into a JSON string, the length of the follow-up JSON string should be the same as the original JSON
     * string.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test17(String source_in) {  // Fixed
        /* Get source output */
        JSONObject sourceObj = JSON.parseObject(source_in);
        String source_out = sourceObj.toJSONString();

        /* Construct follow-up input */
        TreeMap<String, Object> sortedObj = new TreeMap<>(sourceObj);
        JSONObject followObj = new JSONObject(sortedObj);
        String follow_out = followObj.toJSONString();

        /* Verification */
        assertEquals(source_out.length(), follow_out.length());
    }

    /**
     * Metamorphic Relation 18: The input is a JSON string representing an array of objects. Reordering the objects by their
     * keys and converting it into a JSON string, the length of the follow-up JSON string should be the same as the original
     * JSON string.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void test18(String source_in) {
        /* Get source output */
        JSONArray sourceArray = JSON.parseArray(source_in);
        String source_out = sourceArray.toJSONString();

        /* Construct follow-up input */
        JSONArray followArray = JSON.parseArray(source_in);
        followArray.sort(null);

        /* Get follow-up output */
        String follow_out = followArray.toJSONString();

        /* Verification */
        assertEquals(source_out.length(), follow_out.length());
    }

    /**
     * Metamorphic Relation 19: The input is a valid JSON object. Receiving the JSON object, removing all null or empty fields to form a new object
     * and then converting the new object to a JSON string, the length of the follow-up JSON string should be the same as or less than the original JSON string.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test19(String source_in) {
        JSONObject jsonObj = JSON.parseObject(source_in);

        /* Get source output */
        String source_out = jsonObj.toJSONString();

        /* Construct follow-up input */
        JSONObject followObj = new JSONObject(jsonObj);
        followObj.keySet().removeIf(key -> {
            Object value = followObj.get(key);
            return value == null || (value instanceof String && ((String) value).isEmpty());
        });

        /* Get follow-up output */
        String follow_out = followObj.toJSONString();

        /* Verification */
        assertTrue(follow_out.length() <= source_out.length());
    }

    /**
     * Metamorphic Relation 20: The input is a JSON string representing an array of objects. Removing all objects from the array with a certain field value and converting it into a
     * JSON string, the length of the follow-up JSON string should be less than or equal to the original JSON string.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void test20(String source_in) {
        /* Get source output */
        JSONArray sourceArray = JSON.parseArray(source_in);
        String source_out = sourceArray.toJSONString();

        /* Construct follow-up input */
        JSONArray followArray = JSON.parseArray(source_in);
        followArray.removeIf(jsonObj -> jsonObj instanceof JSONObject && ((JSONObject) jsonObj).containsValue("certainFieldValue"));

        /* Get follow-up output */
        String follow_out = followArray.toJSONString();

        /* Verification */
        assertTrue(follow_out.length() <= source_out.length());
    }

    /**
     * Metamorphic Relation 21: The input is a JSON string representing an object. Redacting all sensitive information fields from the original object and
     * converting it into a JSON string, the length of the follow-up JSON string should be less than or equal to the original JSON string.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test21(String source_in) {
        /* Get source output */
        JSONObject sourceObj = JSON.parseObject(source_in);
        String source_out = sourceObj.toJSONString();

        /* Construct follow-up input */
        JSONObject followObj = JSON.parseObject(source_in);
        followObj.remove("password");
        followObj.remove("creditCardNumber");

        /* Get follow-up output */
        String follow_out = followObj.toJSONString();

        /* Verification */
        assertTrue(follow_out.length() <= source_out.length());
    }

    /**
     * Metamorphic Relation 22: The input is a JSON object. Converting the JSON object into a string s1,
     * after adding spaces and line breaks to s1 and converting it back into an object, the resulting object should have the
     * same content as the original object.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test22(String source_in) {  // Fixed
        JSONObject sourceObj = JSON.parseObject(source_in);

        /* Get source output */
        String s1 = sourceObj.toJSONString();
        String formattedString = formatJsonString(s1);
        JSONObject followObj = JSON.parseObject(formattedString);

        /* Verification */
        assertEquals(sourceObj, followObj);
    }

    private static String formatJsonString(String s) {
        Gson gson = new GsonBuilder().setPrettyPrinting().create();
        JsonParser jp = new JsonParser();
        JsonElement je = jp.parse(s);
        return gson.toJson(je);
    }

    /**
     * Metamorphic Relation 23: The input is a JSON string representing an array of objects. Generating a distinct set of elements from
     * the array and converting it into a JSON string, the length of the follow-up JSON string should be less than or equal to the original
     * JSON string.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void test23(String source_in) {
        /* Get source output */
        JSONArray sourceArray = JSON.parseArray(source_in);
        String source_out = sourceArray.toJSONString();

        /* Construct follow-up input */
        Set<Object> followSet = new HashSet<>(sourceArray);

        /* Get follow-up output */
        String follow_out = followSet.toString();

        /* Verification */
        assertTrue(follow_out.length() <= source_out.length());
    }

    /**
     * Metamorphic Relation 24: The input is a JSON string representing an array of objects. Replacing a subset of the elements in
     * the array with a new set of elements and converting it into a JSON string, the length of the follow-up JSON string should be
     * the same as the original JSON string.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void test24(String source_in) {
        /* Get source output */
        JSONArray sourceArray = JSON.parseArray(source_in);
        String source_out = sourceArray.toJSONString();

        /* Construct follow-up input */
        List<Object> followList = new ArrayList<>(sourceArray);
        followList.subList(0, sourceArray.size() / 2).clear();

        /* Get follow-up output */
        String follow_out = new JSONArray(followList).toJSONString();

        /* Verification */
        assertEquals(source_out.length(), follow_out.length());
    }

    /**
     * Metamorphic Relation 25: The input is a JSON string. Appending the same JSON string to itself and converting it into a new JSON
     * string, the length of the follow-up JSON string should be greater than or equal to the original JSON string.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test25(String source_in) {
        /* Get source output */
        String source_out = source_in;

        /* Construct follow-up input */
        String follow_in = source_in + source_in;

        /* Get follow-up output */
        String follow_out = JSON.parse(follow_in).toString();

        /* Verification */
        assertTrue(follow_out.length() >= source_out.length());
    }

    /**
     * Metamorphic Relation 26: The input is a JSON string representing an object. Replacing a subset of the values in the object with the
     * same set of values and converting it into a JSON string, the length of the follow-up JSON string should be the same as the original
     * JSON string.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test26(String source_in) {  // Fixed
        /* Get source output */
        JSONObject sourceObj = JSON.parseObject(source_in);
        String source_out = sourceObj.toJSONString();

        /* Construct follow-up input */
        JSONObject followObj = JSON.parseObject(source_in);
        for (String key : followObj.keySet()) {
            followObj.put(key, "newValue");
        }

        /* Get follow-up output */
        String follow_out = followObj.toJSONString();

        /* Verification */
        assertEquals(source_out.length(), follow_out.length());
    }

    /**
     * Metamorphic Relation 27: The input is a JSON string representing an array of objects. Converting the array into a JSON string, and then
     * converting the string back into an array of objects, the original array should be equal to the array converted back from the string.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void test27(String source_in) {
        /* Get source output */
        JSONArray sourceArray = JSON.parseArray(source_in);
        String jsonString = sourceArray.toJSONString();

        /* Construct follow-up input */
        JSONArray followArray = JSON.parseArray(jsonString);

        /* Verification */
        assertEquals(sourceArray, followArray);
    }

    /**
     * Metamorphic Relation 28: Given a JSON string representing an object, swapping the keys and values of the object and then converting it back
     * into a JSON string. The length of the follow-up JSON string should be the same as or less than the original JSON string.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test28(String source_in) {
        /* Get source output */
        JSONObject sourceObj = JSON.parseObject(source_in);
        String source_out = sourceObj.toJSONString();

        /* Construct follow-up input */
        JSONObject followObj = new JSONObject();
        for (Map.Entry<String, Object> entry : sourceObj.entrySet()) {
            followObj.put(entry.getValue().toString(), entry.getKey());
        }

        /* Get follow-up output */
        String follow_out = followObj.toJSONString();

        /* Verification */
        assertTrue(follow_out.length() <= source_out.length());
    }

    /**
     * Metamorphic Relation 29: Given a JSON string representing an object, adding an extra level of nesting to the object and then converting it back into a JSON string.
     * The length of the follow-up JSON string should be greater than the original JSON string.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test29(String source_in) {
        /* Get source output */
        JSONObject sourceObj = JSON.parseObject(source_in);
        String source_out = sourceObj.toJSONString();

        /* Construct follow-up input */
        JSONObject followObj = new JSONObject();
        followObj.put("nestedObject", sourceObj);

        /* Get follow-up output */
        String follow_out = followObj.toJSONString();

        /* Verification */
        assertTrue(follow_out.length() > source_out.length());
    }

    /**
     * Metamorphic Relation 30: Given a JSON string representing an object, removing the duplicate values from the object and then converting it back into a JSON string.
     * The length of the follow-up JSON string should be less than or equal to the original JSON string.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test30(String source_in) {
        /* Get source output */
        JSONObject sourceObj = JSON.parseObject(source_in);
        String source_out = sourceObj.toJSONString();

        /* Construct follow-up input */
        Collection<Object> values = sourceObj.values();
        Set<Object> uniqueValues = new HashSet<>(values);

        /* Get follow-up output */
        String follow_out = uniqueValues.toString();

        /* Verification */
        assertTrue(follow_out.length() <= source_out.length());
    }

    /**
     * Metamorphic Relation 31: Given a JSON string representing an array of objects, filtering the array to contain only objects with a certain field and then converting it back into a JSON string.
     * The length of the follow-up JSON string should be less than or equal to the original JSON string.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void test31(String source_in) {  // Fixed
        /* Get source output */
        JSONArray sourceArray = JSON.parseArray(source_in);
        String source_out = sourceArray.toJSONString();

        /* Construct follow-up input */
        JSONArray followArray = new JSONArray();
        String targetField = "fieldName";
        for (int i = 0; i < sourceArray.size(); i++) {
            String field = sourceArray.getString(i);
            if (field.equals(targetField)) {
                followArray.add(field);
            }
        }

        /* Get follow-up output */
        String follow_out = followArray.toJSONString();

        /* Verification */
        assertTrue(follow_out.length() <= source_out.length());
    }

    /**
     * Metamorphic Relation 32: Given a JSON string representing an array of objects, converting the array into a set of objects and then back into a new JSON string.
     * The length of the follow-up JSON string should be less than or equal to the original JSON string.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void test32(String source_in) {
        /* Get source output */
        JSONArray sourceArray = JSON.parseArray(source_in);
        String source_out = sourceArray.toJSONString();

        /* Construct follow-up input */
        Set<Object> followSet = new HashSet<>(sourceArray);

        /* Get follow-up output */
        String follow_out = followSet.toString();

        /* Verification */
        assertTrue(follow_out.length() <= source_out.length());
    }

    /**
     * Metamorphic Relation 33: Given a JSON string representing an object, adding a new field to the object and then converting it to a JSON string.
     * The length of the follow-up JSON string should be greater than or equal to the original JSON string.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test33(String source_in) {  // Fixed
        /* Get source output */
        JSONObject sourceObj = JSON.parseObject(source_in);
        String source_out = sourceObj.toJSONString();

        /* Construct follow-up input */
        JSONObject followObj = JSON.parseObject(source_out);
        followObj.put("newField", "newValue");

        /* Get follow-up output */
        String follow_out = followObj.toJSONString();

        /* Verification */
        assertTrue(follow_out.length() >= source_out.length());
    }

    /**
     * Metamorphic Relation 34: Given a JSON string representing an array of objects, sorting the array based on a specific field and then converting it to a JSON string.
     * The length of the follow-up JSON string should be the same as the original JSON string.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void test34(String source_in) {  // Fixed
        /* Get source output */
        JSONArray sourceArray = JSON.parseArray(source_in);
        String source_out = sourceArray.toJSONString();

        /* Construct follow-up input */
        JSONArray followArray = JSON.parseArray(source_in);
        followArray.sort(null);

        /* Get follow-up output */
        String follow_out = new JSONArray(followArray).toJSONString();

        /* Verification */
        assertEquals(source_out.length(), follow_out.length());
    }

    /**
     * Metamorphic Relation 35: Given a JSON string representing an array of objects, modifying one of the objects in the array and then converting it to a JSON string.
     * The length of the follow-up JSON string should be the same as the original JSON string.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void test35(String source_in) {
        /* Get source output */
        JSONArray sourceArray = JSON.parseArray(source_in);
        String source_out = sourceArray.toJSONString();

        /* Construct follow-up input */
        JSONArray followArray = JSON.parseArray(source_out);
        JSONObject obj = followArray.getJSONObject(0);
        obj.put("modifiedField", "modifiedValue");

        /* Get follow-up output */
        String follow_out = followArray.toJSONString();

        /* Verification */
        assertEquals(source_out.length(), follow_out.length());
    }

    /**
     * Metamorphic Relation 36: Given a JSON string representing an object, appending a new field with a large value to the object and then converting it to a JSON string.
     * The length of the follow-up JSON string should be greater than the original JSON string.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test36(String source_in) {
        /* Get source output */
        JSONObject sourceObj = JSON.parseObject(source_in);
        String source_out = sourceObj.toJSONString();

        /* Construct follow-up input */
        String largeValue = "x".repeat(10000);
        sourceObj.put("largeField", largeValue);

        /* Get follow-up output */
        String follow_out = sourceObj.toJSONString();

        /* Verification */
        assertTrue(follow_out.length() > source_out.length());
    }

    /**
     * Metamorphic Relation 37: Given a JSON string representing an array of objects, merging multiple arrays and then converting it to a JSON string.
     * The length of the follow-up JSON string should be greater than or equal to the original JSON string.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void test37(String source_in1) { // Fixed
        String source_in2 = "[\"value1\", \"value2\", \"value3\"]";

        /* Get source output */
        JSONArray sourceArray1 = JSON.parseArray(source_in1);
        JSONArray sourceArray2 = JSON.parseArray(source_in2);
        String source_out = sourceArray1.toJSONString();

        /* Construct follow-up input */
        sourceArray1.addAll(sourceArray2);

        /* Get follow-up output */
        String follow_out = sourceArray1.toJSONString();

        /* Verification */
        assertTrue(follow_out.length() >= source_out.length());
    }

    /**
     * Metamorphic Relation 38: Given a JSON string representing an object, serializing the object, and then deserializing the resulting string back to the object.
     * After deserialization, the deserialized object should be equal to the original object.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test38(String source_in) {  // Fixed
        JSONObject jsonObj = JSONObject.parseObject(source_in);

        /* Get source output */
        String serialized = jsonObj.toJSONString();

        /* Construct follow-up input */
        JSONObject deserialized = JSON.parseObject(serialized);

        /* Verification */
        assertEquals(jsonObj, deserialized);
    }

    /**
     * Metamorphic Relation 39: Given a JSON string representing an object, converting the object into a string s1, then modifying the string s1 and converting it back into an object.
     * The resulting object should not be equal to the original object.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test39(String source_in) {
        JSONObject jsonObj = JSON.parseObject(source_in);

        /* Get source output */
        String s1 = jsonObj.toJSONString();

        /* Construct follow-up input */
        String modifiedS1 = s1.replaceAll("key", "modifiedKey");
        JSONObject followObj = JSON.parseObject(modifiedS1);

        /* Verification */
        assertNotEquals(jsonObj, followObj);
    }

    /**
     * Metamorphic Relation 40: Given a JSON string representing an object, converting the object into a string and then converting the string back into an object.
     * The length of the follow-up JSON string should be the same as the original JSON string.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test40(String source_in) {
        JSONObject jsonObj = JSON.parseObject(source_in);

        /* Get source output */
        String source_out = jsonObj.toJSONString();

        /* Construct follow-up input */
        Object follow_out = JSON.parseObject(source_out);

        /* Verification */
        assertEquals(source_out.length(), follow_out.toString().length());
    }

    static Stream<Arguments> testcaseProvider1() throws IOException {
        return testcaseGenerator.generate_s(1000);
    }

    static Stream<Arguments> testcaseProvider2() throws IOException {
        return testcaseGenerator.generate_s_arr(1000);
    }
}
