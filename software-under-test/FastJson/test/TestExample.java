package test;

import com.alibaba.fastjson.JSON;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;
import java.util.HashMap;
import java.util.Iterator;
import java.util.stream.Stream;

import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;

public class TestExample {
    /**
     * Metamorphic Relation 1: The input is a hash table. Converting the hash table
     * into string s1, after adding a piece of data to the hash table and converting
     * it into string s2, the length of s2 is greater than s1.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test1(HashMap<Object, Object> source_in) {
        /* Get source output */
        String source_out = JSON.toJSONString(source_in);

        /* Construct follow-up input */
        HashMap<Object, Object> follow_in = new HashMap<Object, Object>();
        follow_in.putAll(source_in);
        follow_in.put("foo", "bar");

        /* Get follow-up output */
        String follow_out = JSON.toJSONString(follow_in);

        /* Verification */
        assertTrue(follow_out.length() > source_out.length());
    }

    /**
     * Metamorphic Relation 2: The input is a string representing the JSON file's
     * content. Adding a comment to the string, the parse result of the string will
     * be the same.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider2")
    public void test2(String source_in) {
        /* Get source output */
        Object source_out = JSON.parseObject(source_in);

        /* Construct follow-up input */
        String follow_in = source_in + "/* Comment comment comment */";

        /* Get follow-up output */
        Object follow_out = JSON.parseObject(follow_in);

        /* Verification */
        assertEquals(source_out, follow_out);
    }

    /**
     * Metamorphic Relation 3: The input is a hash table. Swapping the value of a
     * pair of key and value and converting the hash table to the string, the output
     * length should be the same as or less than the original.
     */
    @ParameterizedTest
    @MethodSource("testcaseProvider1")
    public void test3(HashMap<Object, Object> source_in) {
        /* Get source output */
        String source_out = JSON.toJSONString(source_in);

        /* Construct follow-up input */
        HashMap<Object, Object> follow_in = new HashMap<Object, Object>();
        follow_in.putAll(source_in);
        Iterator<Object> it = follow_in.keySet().iterator();
        Object k = it.next();
        Object v = follow_in.get(k);
        follow_in.remove(k);
        follow_in.put(v, k);

        /* Get follow-up output */
        String follow_out = JSON.toJSONString(follow_in);

        /* Verification */
        assertTrue(source_out.length() >= follow_out.length());
    }

    static Stream<Arguments> testcaseProvider1() {
        /* Testcase 1 */
        HashMap<Object, Object> tc1 = new HashMap<Object, Object>();
        tc1.put("name", "zjm");
        tc1.put("age", 25);

        return Stream.of(Arguments.of(tc1));
    }

    static Stream<Arguments> testcaseProvider2() {
        /* Testcase 1 */
        String tc1 = "{\"name\":\"zjm\",\"age\":25}";

        return Stream.of(Arguments.of(tc1));
    }
}
