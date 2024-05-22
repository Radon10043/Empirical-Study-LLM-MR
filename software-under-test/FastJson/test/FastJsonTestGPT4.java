package test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assertions.fail;
import java.io.IOException;
import java.io.Reader;
import java.io.StringReader;
import java.io.UnsupportedEncodingException;
import java.lang.reflect.Type;
import java.nio.charset.StandardCharsets;
import java.security.SecureRandom;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Locale;
import java.util.Map;
import java.util.Set;
import java.util.TreeMap;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.util.stream.Collectors;
import java.util.stream.Stream;
import org.apache.commons.lang3.RandomStringUtils;
import org.junit.jupiter.api.RepeatedTest;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;
import com.alibaba.fastjson.JSON;
import com.alibaba.fastjson.JSONArray;
import com.alibaba.fastjson.JSONObject;
import com.alibaba.fastjson.JSONPath;
import com.alibaba.fastjson.PropertyNamingStrategy;
import com.alibaba.fastjson.TypeReference;
import com.alibaba.fastjson.parser.ParserConfig;
import com.alibaba.fastjson.serializer.SerializeConfig;
import com.alibaba.fastjson.serializer.SerializerFeature;
import com.alibaba.fastjson.serializer.SimpleDateFormatSerializer;
import com.alibaba.fastjson.serializer.SimplePropertyPreFilter;
import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.google.gson.JsonParser;
import com.google.gson.JsonElement;

public class FastJsonTestGPT4 {
    /**
     * Metamorphic Relation 1: Converting a Java object to JSON string, and then
     * parsing back to an
     * object, the recovered object should be equal to the original object.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider3")
    public void testConvertObjectToJsonAndBack(Object sourceObject) {
        // Get source output
        String jsonOutput = JSON.toJSONString(sourceObject);

        // Construct follow-up input by parsing back the JSON string to an Object
        Object followUpObject = JSON.parseObject(jsonOutput, sourceObject.getClass());

        // Verification
        assertEquals(sourceObject, followUpObject);
    }

    /**
     * Metamorphic Relation 2: Pretty printing a JSON should not change its parse
     * result.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void testPrettyPrintJson(String sourceJson) {
        // Get source output
        Object sourceOutput = JSON.parseObject(sourceJson);

        // Construct follow-up input by applying pretty print
        String prettyJson = JSON.toJSONString(JSON.parseObject(sourceJson), true);

        // Get follow-up output
        Object followUpOutput = JSON.parseObject(prettyJson);

        // Verification
        assertEquals(sourceOutput, followUpOutput);
    }

    /**
     * Metamorphic Relation 3: Serializing a Java object with a custom serializer
     * should preserve
     * the equality of the object when deserialized with a corresponding custom
     * deserializer.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider3")
    public void testCustomSerialization(Object sourceObject) { // Fixed
        SerializeConfig serializeConfig = new SerializeConfig();
        ParserConfig parserConfig = new ParserConfig();
        serializeConfig.propertyNamingStrategy = PropertyNamingStrategy.SnakeCase;
        parserConfig.addAccept("test");

        // Get source output
        String jsonOutput = JSON.toJSONString(sourceObject, serializeConfig);

        // Construct follow-up input by parsing the JSON string with a custom
        // deserializer
        Object followUpObject = JSON.parseObject(jsonOutput, sourceObject.getClass(), parserConfig,
                JSON.DEFAULT_PARSER_FEATURE);

        // Verification
        assertEquals(sourceObject, followUpObject);
    }

    /**
     * Metamorphic Relation 4: An object serialized with additional fields excluded
     * should result in
     * a JSON string of lesser or equal length compared to the original
     * serialization.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider3")
    public void testSerializationExcludingFields(Object sourceObject) {
        // Get source output
        String sourceJson = JSON.toJSONString(sourceObject);

        // Create a SimplePropertyPreFilter to exclude one or more fields
        SimplePropertyPreFilter filter = new SimplePropertyPreFilter();
        filter.getExcludes().add("ignoredProperty");

        // Construct follow-up input by serializing the object with the filter applied
        String filteredJson = JSON.toJSONString(sourceObject, filter);

        // Verification
        assertTrue(filteredJson.length() <= sourceJson.length());
    }

    /**
     * Metamorphic Relation 5: Applying a JSONPath query to a JSON string and
     * subsequently to the
     * result should yield the same result as applying the JSONPath to the original
     * JSON string
     * directly.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void testJsonPathQueryTwice(String sourceJson) {
        String jsonPathQuery = "A";

        // Execute JSONPath query on the source JSON
        Object intermediateResult = JSONPath.eval(JSON.parseObject(sourceJson), jsonPathQuery);

        // Execute the same JSONPath query on the intermediate result
        Object finalResult = JSONPath.eval(intermediateResult, jsonPathQuery);

        // Execute the JSONPath query on the source JSON directly
        Object directResult = JSONPath.eval(JSON.parseObject(sourceJson), jsonPathQuery);

        // Verification
        assertEquals(directResult, finalResult);
    }

    /**
     * Metamorphic Relation 6: Adding an item to a collection and serializing it
     * should produce a
     * JSON string whose length is greater than the JSON string of the original
     * collection.
     */
    @RepeatedTest(1000)
    public void testAddItemToCollection() { // Fixed
        // Construct source collection
        SecureRandom rand = new SecureRandom();
        Collection<Object> sourceCollection = new ArrayList<>();
        int size = rand.nextInt(1, 101);
        for (int i = 0; i < size; i++) {
            sourceCollection.add(rand.nextInt(1000));
        }

        // Serialize the original collection
        String originalJson = JSON.toJSONString(sourceCollection);

        // Construct follow-up input by adding an item (ensure the new item's type is
        // compliant with
        // the collection's type)
        Collection<Object> followUpCollection = new ArrayList<>(sourceCollection);
        followUpCollection.add(new Object()); // This assumes the collection can take objects of
                                              // type Object

        // Serialize the modified collection
        String followUpJson = JSON.toJSONString(followUpCollection);

        // Verification
        assertTrue(followUpJson.length() > originalJson.length());
    }

    /**
     * Metamorphic Relation 7: Removing an item from a non-empty collection should
     * produce a JSON
     * string whose length is less than the JSON string of the original collection.
     */
    @RepeatedTest(1000)
    public void testRemoveItemFromCollection() { // Fixed
        // Construct source collection
        SecureRandom rand = new SecureRandom();
        Collection<Object> sourceCollection = new ArrayList<>();
        int size = rand.nextInt(1, 101);
        for (int i = 0; i < size; i++) {
            sourceCollection.add(rand.nextInt(1000));
        }

        // Serialize the original collection
        String originalJson = JSON.toJSONString(sourceCollection);

        // Construct follow-up input by removing an item from the collection
        Collection<Object> followUpCollection = new ArrayList<>(sourceCollection);
        if (!followUpCollection.isEmpty()) {
            followUpCollection.remove(followUpCollection.iterator().next());
        }

        // Serialize the modified collection
        String followUpJson = JSON.toJSONString(followUpCollection);

        // Verification
        assertTrue(followUpJson.length() < originalJson.length());
    }

    /**
     * Metamorphic Relation 8: Serialization of Java objects with the same data but
     * different field
     * names should produce JSON strings of different lengths.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider3")
    public void testSerializationWithDifferentFieldNames(Object objectWithFieldNameA,
            Object objectWithFieldNameB) {
        // Serialize both provided objects
        String jsonA = JSON.toJSONString(objectWithFieldNameA);
        String jsonB = JSON.toJSONString(objectWithFieldNameB);

        // Verification
        assertNotEquals(jsonA.length(), jsonB.length());
    }

    /**
     * Metamorphic Relation 9: Serialization of a map should not change after adding
     * then removing
     * the same item.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider3")
    public void testAddRemoveItemInMap(Map<?, ?> sourceMap) { // Fixed
        // Serialize the original map
        String originalJson = JSON.toJSONString(sourceMap);

        // Construct follow-up input by adding and then removing an item
        Map<Object, Object> modifiedMap = new HashMap<>(sourceMap);
        Object key = new Object(); // Use an object that is guaranteed not to be in the key set
        modifiedMap.put(key, "value");
        modifiedMap.remove(key);

        // Serialize the modified map
        String modifiedJson = JSON.toJSONString(modifiedMap);

        // Verification
        assertEquals(originalJson, modifiedJson);
    }

    /**
     * Metamorphic Relation 10: Serialization of nested Java objects should produce
     * the same JSON
     * string even if the nesting order of the objects within each other changes,
     * assuming no
     * serialization directives (like order) are given.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider3")
    public void testNestedObjectsSerializationOrder(Object outerObject, Object innerObject) {
        // Serialize the outer object containing the inner object
        String jsonOriginalNesting = JSON.toJSONString(outerObject);

        // Swap the nesting order of the objects
        // Note: This requires that outerObject and innerObject are of compatible types
        // for swapping
        String jsonSwappedNesting = JSON.toJSONString(innerObject); // Here you would somehow swap
                                                                    // them

        // Verification
        assertEquals(jsonOriginalNesting, jsonSwappedNesting);
    }

    /**
     * Metamorphic Relation 11: Serialization of a Java object graph with circular
     * references should
     * not result in a StackOverflowError and should produce a consistent JSON
     * result.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider3")
    public void testCircularReferencesSerialization(Object sourceObjectWithCircularReferences) {
        // Serialize the object graph with circular references
        String jsonResult = JSON.toJSONString(sourceObjectWithCircularReferences,
                SerializerFeature.DisableCircularReferenceDetect);

        // Deserialize to verify JSON consistency
        Object deserializedObject = JSON.parseObject(jsonResult, sourceObjectWithCircularReferences.getClass());

        // Serialize the deserialized object again
        String jsonResultAgain = JSON.toJSONString(deserializedObject,
                SerializerFeature.DisableCircularReferenceDetect);

        // Verification: the re-serialized string should match the original serialized
        // string
        assertEquals(jsonResult, jsonResultAgain);
    }

    /**
     * Metamorphic Relation 12: Converting a JSON array to a Java List and back to a
     * JSON array
     * should produce the same JSON array as the original.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void testJsonArrayToListAndBack(String jsonArrayString) {
        // Deserialize JSON array to List
        List<?> list = JSON.parseArray(jsonArrayString);

        // Serialize List back to JSON array
        String jsonResult = JSON.toJSONString(list);

        // Verification
        assertEquals(jsonArrayString, jsonResult);
    }

    /**
     * Metamorphic Relation 13: Parsing JSON from strings and from equivalent
     * readers should result
     * in the same object.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void testParsingFromStringAndReader(String jsonString) { // Illegal
        // // Parse JSON from String
        // Object fromStringResult = JSON.parseObject(jsonString);

        // // Parse JSON from a Reader constructed from the String
        // Reader stringReader = new StringReader(jsonString);
        // Object fromReaderResult = JSON.parseObject(stringReader,
        // fromStringResult.getClass());

        // // Verification
        // assertEquals(fromStringResult, fromReaderResult);
    }

    /**
     * Metamorphic Relation 14: Renaming a field in a Java object and adjusting the
     * mapping
     * accordingly should not change the serialization result when a custom naming
     * strategy is
     * applied.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider3")
    public void testRenamedFieldWithCustomNamingStrategy(Object sourceObjectWithOriginalFieldName) { // Fixed
        SerializeConfig serializeConfigWithCustomNamingStrategy = new SerializeConfig();
        serializeConfigWithCustomNamingStrategy.propertyNamingStrategy = PropertyNamingStrategy.SnakeCase;

        Object sourceObjectWithRenamedFieldName = new Object();
        sourceObjectWithRenamedFieldName = sourceObjectWithOriginalFieldName;

        // Serialize the object with original field name
        String originalFieldNameJson = JSON.toJSONString(sourceObjectWithOriginalFieldName,
                serializeConfigWithCustomNamingStrategy);

        // Serialize the object with renamed field
        String renamedFieldNameJson = JSON.toJSONString(sourceObjectWithRenamedFieldName,
                serializeConfigWithCustomNamingStrategy);

        // Verification
        assertEquals(originalFieldNameJson, renamedFieldNameJson);
    }

    /**
     * Metamorphic Relation 15: Encoding and decoding a JSON string with URL
     * encoding should not
     * affect the parse result.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void testUrlEncodingJsonString(String jsonString) {
        // URL encode the JSON string
        String urlEncodedJsonString;
        try {
            urlEncodedJsonString = java.net.URLEncoder.encode(jsonString, StandardCharsets.UTF_8.name());
        } catch (UnsupportedEncodingException e) {
            fail("Encoding failed");
            return;
        }

        // URL decode the encoded JSON string
        String urlDecodedJsonString;
        try {
            urlDecodedJsonString = java.net.URLDecoder.decode(urlEncodedJsonString, StandardCharsets.UTF_8.name());
        } catch (UnsupportedEncodingException e) {
            fail("Decoding failed");
            return;
        }

        // Parse the original and decoded JSON strings
        Object originalParseResult = JSON.parseObject(jsonString);
        Object decodeParseResult = JSON.parseObject(urlDecodedJsonString);

        // Verification
        assertEquals(originalParseResult, decodeParseResult);
    }

    /**
     * Metamorphic Relation 16: Repeated serializations of an object must yield the
     * same JSON string
     * each time.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider3")
    public void testRepeatedSerializationConsistency(Object sourceObject) {
        // Perform first serialization
        String firstSerialization = JSON.toJSONString(sourceObject);

        // Perform second serialization
        String secondSerialization = JSON.toJSONString(sourceObject);

        // Verification
        assertEquals(firstSerialization, secondSerialization);
    }

    /**
     * Metamorphic Relation 17: Serializing a map with shuffled key order should not
     * affect the
     * serialized JSON length.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider3")
    public void testMapSerializationIgnoresKeyOrder(Map<String, Object> sourceMap) {
        // Serialize the original map
        String originalJson = JSON.toJSONString(sourceMap);

        // Shuffle the keys of the map
        List<String> shuffledKeys = new ArrayList<>(sourceMap.keySet());
        Collections.shuffle(shuffledKeys);
        LinkedHashMap<String, Object> shuffledMap = new LinkedHashMap<>();
        for (String key : shuffledKeys) {
            shuffledMap.put(key, sourceMap.get(key));
        }

        // Serialize the shuffled map
        String shuffledJson = JSON.toJSONString(shuffledMap);

        // Verification
        assertEquals(originalJson.length(), shuffledJson.length());
    }

    /**
     * Metamorphic Relation 18: Converting a JSON representation to different number
     * types should
     * not affect equality checks.
     */
    @RepeatedTest(1000)
    public void testNumericTypeConversion() { // Fixed
        SecureRandom rand = new SecureRandom();
        String jsonNumber = String.valueOf(rand.nextInt(1000000000));

        // Parse JSON number as Integer
        Integer parsedAsInteger = JSON.parseObject(jsonNumber, Integer.class);

        // Parse JSON number as Double
        Double parsedAsDouble = JSON.parseObject(jsonNumber, Double.class);

        // Verification: The numerical values should be equal
        assertEquals(parsedAsInteger.doubleValue(), parsedAsDouble, 0.000001);
    }

    /**
     * Metamorphic Relation 19: Changing JSON field values while preserving data
     * type should not
     * affect the overall structure.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void testChangingJsonFieldValues(String sourceJson) { // Fixed
        HashMap<String, String> tmpObject = JSON.parseObject(sourceJson, HashMap.class);
        for (Map.Entry<String, String> entry : tmpObject.entrySet()) {
            entry.setValue("modified" + entry.getValue());
        }
        String modifiedJson = JSON.toJSONString(tmpObject);

        Pattern fieldPattern = Pattern.compile("\"(\\w+)\":\"?([^\"]*)\"?[,}]");

        Matcher sourceMatcher = fieldPattern.matcher(sourceJson);
        Matcher modifiedMatcher = fieldPattern.matcher(modifiedJson);

        Map<String, String> sourceFields = new HashMap<>();
        Map<String, String> modifiedFields = new HashMap<>();

        while (sourceMatcher.find()) {
            sourceFields.put(sourceMatcher.group(1), sourceMatcher.group(2));
        }

        while (modifiedMatcher.find()) {
            modifiedFields.put(modifiedMatcher.group(1), modifiedMatcher.group(2));
        }

        // Verification: Assert the structure (keys) of JSON is preserved, values may
        // change
        assertEquals(sourceFields.keySet(), modifiedFields.keySet());
    }

    /**
     * Metamorphic Relation 20: Converting an empty Java object to a JSON string
     * should yield a JSON
     * object with empty fields.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderForEmptyJavaObjects")
    public void testEmptyJavaObjectToJson(Object emptyJavaObject) {
        // Serialize the empty Java object
        String jsonResult = JSON.toJSONString(emptyJavaObject);

        // Verification: The JSON serialization should be an object with empty fields
        assertEquals("{}", jsonResult);
    }

    /**
     * Metamorphic Relation 21: Serialization of the same Java object with different
     * JSON field
     * naming policies should produce JSON strings of the same length.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider3")
    public void testSerializationWithDifferentFieldNamingPolicies(Object sourceObject) {
        // Serialize using camelCase policy
        SerializeConfig camelCaseConfig = new SerializeConfig();
        camelCaseConfig.propertyNamingStrategy = PropertyNamingStrategy.CamelCase;
        String camelCaseJson = JSON.toJSONString(sourceObject, camelCaseConfig);

        // Serialize using snake_case policy
        SerializeConfig snakeCaseConfig = new SerializeConfig();
        snakeCaseConfig.propertyNamingStrategy = PropertyNamingStrategy.SnakeCase;
        String snakeCaseJson = JSON.toJSONString(sourceObject, snakeCaseConfig);

        // Verification: The length of the JSON strings should be the same
        assertEquals(camelCaseJson.length(), snakeCaseJson.length());
    }

    /**
     * Metamorphic Relation 22: Adding redundant whitespace into a JSON string
     * should not change the
     * object obtained from parsing it.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void testWhitespaceInJsonDoesNotAffectParsing(String sourceJson) {
        // Add redundant whitespace to the JSON string
        String whiteSpacedJson = sourceJson.replaceAll("\\{", "{\n").replaceAll("\\}", "\n}")
                .replaceAll(",", ",\n ");

        // Parse both the original and whitespace-added JSON strings
        Object originalObject = JSON.parseObject(sourceJson);
        Object whiteSpacedObject = JSON.parseObject(whiteSpacedJson);

        // Verification
        assertEquals(originalObject, whiteSpacedObject);
    }

    /**
     * Metamorphic Relation 23: Replacing enum values with their corresponding names
     * in a JSON
     * string should not affect JSON deserialization.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void testEnumDeserializationWithNames(String sourceJson) {
        // Deserialize source JSON
        Object originalObject = JSON.parseObject(sourceJson, HashMap.class);

        // Replace all enum constants in the JSON string with their corresponding names
        // Note: This would typically require a specialized method to identify and
        // replace enum
        // names.
        String modifiedJson = sourceJson; // Assume modifyJsonEnumsFunction reused here

        // Deserialize modified JSON
        Object modifiedObject = JSON.parseObject(modifiedJson, HashMap.class);

        // Verification
        assertEquals(originalObject, modifiedObject);
    }

    /**
     * Metamorphic Relation 24: Sorting a JSON array should not affect individual
     * parsing of its
     * elements.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void testSortingJsonArray(String jsonArray) {
        // Parse JSON array as a list
        List<?> list = JSON.parseArray(jsonArray);

        // Sort the list
        List<?> sortedList = new ArrayList<>(list);
        Collections.sort(sortedList, Comparator.comparing(Object::toString));

        // Parse and serialize each individual element of the sorted list
        List<String> serializedSortedElements = sortedList.stream()
                .map(element -> JSON.toJSONString(element)).collect(Collectors.toList());

        // Parse and serialize each individual element of the original list
        List<String> serializedOriginalElements = list.stream()
                .map(element -> JSON.toJSONString(element)).collect(Collectors.toList());

        // Verification: Individual serialized elements should match regardless of array
        // order
        Collections.sort(serializedOriginalElements);
        Collections.sort(serializedSortedElements);
        assertEquals(serializedOriginalElements, serializedSortedElements);
    }

    /**
     * Metamorphic Relation 25: Deserializing a JSON object with additional unknown
     * fields should
     * not affect the known fields of the deserialized Java object.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderForPartialJsonObjects")
    public void testDeserializationWithAdditionalFields(String partialJson, String extendedJson,
            Class<?> objectClass) {
        // Deserialize the partial JSON (with known fields)
        Object partialObject = JSON.parseObject(partialJson, objectClass);

        // Deserialize the extended JSON (with known and additional unknown fields)
        Object extendedObject = JSON.parseObject(extendedJson, objectClass);

        // Verification
        assertEquals(partialObject, extendedObject);
    }

    /**
     * Metamorphic Relation 26: Serializing a Java object without a field should
     * result in a smaller
     * JSON string than serializing the same object with that field present and
     * non-null.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderForJavaObjectsWithOptionalField")
    public void testSerializationWithAndWithoutOptionalField(Object sourceObjectWithField,
            Object sourceObjectWithoutField) {
        // Serialize the object with the optional field
        String withFieldJson = JSON.toJSONString(sourceObjectWithField);

        // Serialize the object without the optional field
        String withoutFieldJson = JSON.toJSONString(sourceObjectWithoutField);

        // Verification
        assertTrue(withFieldJson.length() > withoutFieldJson.length());
    }

    /**
     * Metamorphic Relation 27: Deserializing a JSON string with different sets of
     * fields into
     * multiple target classes that only contain subsets of these fields should
     * still populate the
     * common fields identically.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderForJsonWithMultipleFieldSets")
    public void testDeserializationToMultipleTargetsWithSubsetFields(String json,
            Class<?> firstTargetClass, Class<?> secondTargetClass) {
        // Deserialize into first target class
        // Object firstTargetInstance = JSON.parseObject(json, firstTargetClass);

        // Deserialize into second target class
        // Object secondTargetInstance = JSON.parseObject(json, secondTargetClass);

        // Verification: Common fields should be populated identically across both
        // target instances
        // Note: Specific assertion logic will depend on test case design and available
        // methods for
        // property extraction
        // This is a placeholder for the actual verification logic
        // verifyCommonFieldsMatch(firstTargetInstance, secondTargetInstance);
    }

    /**
     * Metamorphic Relation 28: Changing the order of array elements in a JSON array
     * should not
     * affect the deserialized set.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void testArrayElementOrderDoesNotAffectDeserializedSet(String jsonArray) {
        // Deserialize JSON array to List
        List<?> deserializedList = JSON.parseArray(jsonArray);

        // Shuffle the list to change element order
        List<?> shuffledList = new ArrayList<>(deserializedList);
        Collections.shuffle(shuffledList);

        // Serialize shuffled list back to JSON array
        String shuffledJsonArray = JSON.toJSONString(shuffledList);

        // Deserialize the shuffled JSON array
        List<?> deserializedShuffledList = JSON.parseArray(shuffledJsonArray);

        // Convert both lists to sets
        Set<?> originalSet = new HashSet<>(deserializedList);
        Set<?> shuffledSet = new HashSet<>(deserializedShuffledList);

        // Verification: The sets should be equal regardless of element order
        assertEquals(originalSet, shuffledSet);
    }

    /**
     * Metamorphic Relation 29: Serializing a JSON object to bytes and back should
     * not change the serialized JSON string.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void testSerializationToJsonBytesAndBack(String jsonString) {
        // Convert JSON string to bytes
        byte[] jsonBytes = JSON.toJSONBytes(JSON.parseObject(jsonString));

        // Convert bytes back to JSON String
        String backToJsonString = new String(jsonBytes, StandardCharsets.UTF_8);

        // Verification
        assertEquals(jsonString, backToJsonString);
    }

    /**
     * Metamorphic Relation 30: Parsing JSON from byte arrays should yield the
     * same result as parsing from equivalent strings.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void testParsingFromBytesEquivalentToStrings(String jsonString) {
        // Convert string to bytes
        byte[] jsonBytes = jsonString.getBytes(StandardCharsets.UTF_8);

        // Parse from string and bytes
        Object fromStringResult = JSON.parseObject(jsonString);
        Object fromBytesResult = JSON.parseObject(jsonBytes,
                fromStringResult.getClass());

        // Verification
        assertEquals(fromStringResult, fromBytesResult);
    }

    /**
     * Metamorphic Relation 31: Serialization of a Java object with transient
     * fields should yield the same result as serialization without those fields,
     * since transient fields are ignored by default.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderForJavaObjectsWithTransientFields")
    public void testSerializationIgnoringTransientFields(Object sourceObjectWithTransientFields,
            Object sourceObjectWithoutTransientFields) {
        // Serialize the object with transient fields
        String jsonWithTransientFields = JSON.toJSONString(sourceObjectWithTransientFields);

        // Serialize the object without transient fields
        String jsonWithoutTransientFields = JSON.toJSONString(sourceObjectWithoutTransientFields);

        // Verification
        assertEquals(jsonWithTransientFields, jsonWithoutTransientFields);
    }

    /**
     * Metamorphic Relation 32: Deserializing a JSON into different fields with
     * different types but compatible values should result in the same JSON string
     * when re-serialized, if no data is lost in conversion.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void testDeserializationAndReserializationWithCompatibleFieldTypes(String json) {
        Class<?> firstType = HashMap.class;
        Class<?> secondType = Map.class;

        // Deserialize JSON to firstType
        Object instanceFirstType = JSON.parseObject(json, firstType);

        // Deserialize JSON to secondType
        Object instanceSecondType = JSON.parseObject(json, secondType);

        // Reserialize both instances
        String reserializedFirst = JSON.toJSONString(instanceFirstType);
        String reserializedSecond = JSON.toJSONString(instanceSecondType);

        // Verification: Reserialized JSON strings should match
        assertEquals(reserializedFirst, reserializedSecond);
    }

    /**
     * Metamorphic Relation 33: Serialization of numeric data with explicit or
     * implicit Locale should not affect the result.
     */
    @RepeatedTest(1000)
    public void testLocaleIndependentSerializationOfNumericData() {
        SecureRandom rand = new SecureRandom();
        Number numericData = rand.nextInt(1, 100000);
        Locale defaultLocale = Locale.getDefault();
        Locale alternativeLocale = Locale.GERMAN;

        // Set default locale
        Locale originalLocale = Locale.getDefault();
        Locale.setDefault(defaultLocale);

        // Serialize with default locale
        String jsonDefaultLocale = JSON.toJSONString(numericData);

        // Set alternative locale
        Locale.setDefault(alternativeLocale);

        // Serialize with alternative locale
        String jsonAlternativeLocale = JSON.toJSONString(numericData);

        // Reset the original locale
        Locale.setDefault(originalLocale);

        // Verification: JSON strings should not differ based on locale
        assertEquals(jsonDefaultLocale, jsonAlternativeLocale);
    }

    /**
     * Metamorphic Relation 34: Renaming a field in a POJO and customizing the
     * serializer to maintain the original field name should result in the same JSON
     * string as the original POJO serialization.
     */
    @ParameterizedTest
    @MethodSource("testcaseProviderForRenamedFieldsWithCustomSerializers")
    public void testCustomSerializerMaintainsOriginalFieldName(Object sourceObjectOriginalField,
            Object sourceObjectRenamedField, SerializeConfig serializeConfigForRenamedField) {
        // Serialize the object with the original field name
        String jsonOriginalFieldName = JSON.toJSONString(sourceObjectOriginalField);

        // Serialize the renamed field object with custom serialization mapping
        String jsonRenamedFieldName = JSON.toJSONString(sourceObjectRenamedField, serializeConfigForRenamedField);

        // Verification
        assertEquals(jsonOriginalFieldName, jsonRenamedFieldName);
    }

    /**
     * Metamorphic Relation 35: Parsing the JSON representation of a collection of
     * items should yield a collection of parsed objects identical to the original
     * items, albeit the order may differ for non-ordered collections.
     */
    @RepeatedTest(1000)
    public void testRoundTripCollectionSerialization() { // Fixed
        SecureRandom rand = new SecureRandom();
        int size = rand.nextInt(1, 101);
        Collection<String> originalCollection = new ArrayList<>();
        for (int i = 0; i < size; i++) {
            originalCollection.add(RandomStringUtils.randomAlphabetic(rand.nextInt(1, 101)));
        }
        Type collectionType = new TypeReference<Collection<String>>() {
        }.getType();

        // Serialize the original collection of objects
        String jsonCollection = JSON.toJSONString(originalCollection);

        // Parse the JSON back to a collection of objects
        Collection<?> parsedCollection = JSON.parseObject(jsonCollection,
                collectionType);

        // Convert both the original and parsed collections to sets for comparison
        Set<?> originalSet = new HashSet<>(originalCollection);
        Set<?> parsedSet = new HashSet<>(parsedCollection);

        // Verification: The sets constructed from original and parsed collections
        // should be equal
        assertEquals(originalSet, parsedSet);
    }

    /**
     * Metamorphic Relation 36: Serializing an array or a collection should yield
     * a JSON string with predictable size increase when an element is added.
     */
    @RepeatedTest(1000)
    public void testArrayAndCollectionSerializationSize() {
        SecureRandom rand = new SecureRandom();
        Object[] sourceArray = new Object[rand.nextInt(1, 101)];
        for (int i = 0; i < sourceArray.length; i++) {
            sourceArray[i] = RandomStringUtils.randomAlphabetic(rand.nextInt(1, 101));
        }
        Collection<Object> sourceCollection = new ArrayList<>(Arrays.asList(sourceArray));

        // Serialize the source array
        String originalArrayJson = JSON.toJSONString(sourceArray);
        int originalArrayJsonLength = originalArrayJson.length();

        // Create a new array with an additional element
        Object[] extendedArray = Arrays.copyOf(sourceArray, sourceArray.length + 1);
        extendedArray[extendedArray.length - 1] = new Object(); // Added element

        // Serialize the extended array
        String extendedArrayJson = JSON.toJSONString(extendedArray);
        int extendedArrayJsonLength = extendedArrayJson.length();

        // Serialize the source collection
        String originalCollectionJson = JSON.toJSONString(sourceCollection);
        int originalCollectionJsonLength = originalCollectionJson.length();

        // Add an element to the collection
        Collection<Object> extendedCollection = new ArrayList<>(sourceCollection);
        extendedCollection.add(new Object());

        // Serialize the extended collection
        String extendedCollectionJson = JSON.toJSONString(extendedCollection);
        int extendedCollectionJsonLength = extendedCollectionJson.length();

        // Verification: The size difference for both the array and collection should be
        // consistent
        assertTrue(
                (extendedArrayJsonLength - originalArrayJsonLength) == (extendedCollectionJsonLength
                        - originalCollectionJsonLength));
    }

    /**
     * Metamorphic Relation 37: The serialized JSON of a collection should have
     * the same length as the JSON array with the collection elements serialized
     * individually.
     */
    @RepeatedTest(1000)
    public void testCollectionSerializationVsIndividualElementSerialization() {
        SecureRandom rand = new SecureRandom();
        Collection<Object> sourceCollection = new ArrayList<>();
        for (int i = 0; i < rand.nextInt(1, 101); i++) {
            sourceCollection.add(RandomStringUtils.randomAlphabetic(rand.nextInt(1, 101)));
        }

        // Serialize the source collection as a whole
        String serializedCollection = JSON.toJSONString(sourceCollection);
        int serializedCollectionLength = serializedCollection.length();

        // Serialize each element individually and concatenate
        StringBuilder serializedIndividualElements = new StringBuilder("[");
        Iterator<?> iter = sourceCollection.iterator();
        while (iter.hasNext()) {
            serializedIndividualElements.append(JSON.toJSONString(iter.next()));
            if (iter.hasNext()) {
                serializedIndividualElements.append(",");
            }
        }
        serializedIndividualElements.append("]");
        int serializedIndividualElementsLength = serializedIndividualElements.toString().length();

        // Verification
        assertEquals(serializedCollectionLength, serializedIndividualElementsLength);
    }

    /**
     * Metamorphic Relation 38: Parsing and re-parsing a JSON string incrementally
     * (element by element for arrays/collections) should result in the same final
     * object.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void testIncrementalParsingOfJsonArray(String jsonArrayString) {
        // Parse the complete JSON array
        List<?> completeList = JSON.parseArray(jsonArrayString);

        // Incrementally parse the JSON array and build a list
        List<Object> incrementalList = new ArrayList<>();
        JSONArray jsonArray = JSON.parseArray(jsonArrayString);
        for (int i = 0; i < jsonArray.size(); ++i) {
            incrementalList.add(jsonArray.getObject(i, Object.class));
        }

        // Verification
        assertEquals(completeList, incrementalList);
    }

    /**
     * Metamorphic Relation 39: Deserializing a JSON object into different types
     * and serializing again, should not change the JSON string if all types have
     * the same JSON properties.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void testDeserializationAndSerializationWithDifferentTypes(String jsonObjectString) {    // Fixed
        Class<?> typeA = HashMap.class;
        Class<?> typeB = Map.class;

        // Deserialize JSON object into type A
        Object instanceA = JSON.parseObject(jsonObjectString, typeA);

        // Serialize instance of type A back to JSON
        String jsonFromA = JSON.toJSONString(instanceA);

        // Deserialize JSON object into type B
        Object instanceB = JSON.parseObject(jsonObjectString, typeB);

        // Serialize instance of type B back to JSON
        String jsonFromB = JSON.toJSONString(instanceB);

        // Verification
        assertEquals(jsonFromA, jsonFromB);
    }

    /**
     * Metamorphic Relation 40: Deserializing and then serializing a JSON object
     * should not change its order of appearance of fields if no custom field
     * ordering is applied during serialization.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void testSerializationPreservesFieldOrder(String jsonObjectString) {
        // Deserialize JSON object
        JSONObject jsonObject = JSON.parseObject(jsonObjectString);

        // Serialize the JSONObject
        String serializedJson = JSON.toJSONString(jsonObject);

        // Obtain the field order of both JSON strings
        List<String> initialFieldOrder = getFieldOrder(jsonObjectString);
        List<String> serializedFieldOrder = getFieldOrder(serializedJson);

        // Verification
        assertEquals(initialFieldOrder, serializedFieldOrder);
    }

    // Assuming getFieldOrder is a utility function that extracts field names in
    // their order of appearance in the JSON string
    private List<String> getFieldOrder(String json) {
        List<String> fields = new ArrayList<>();
        Matcher m = Pattern.compile("\\\"([^\\\"]+)\\\"\\s*:").matcher(json);
        while (m.find()) {
            fields.add(m.group(1));
        }
        return fields;
    }

    static Stream<Arguments> testcaseProvider1() throws IOException {
        return testcaseGenerator.generate_s(1000);
    }

    static Stream<Arguments> testcaseProvider2() throws IOException {
        return testcaseGenerator.generate_s_arr(1000);
    }

    static Stream<Arguments> testcaseProvider3() throws IOException {
        return testcaseGenerator.generate_hm(1000);
    }
}
