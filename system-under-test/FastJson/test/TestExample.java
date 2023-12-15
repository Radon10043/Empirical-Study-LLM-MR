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
     * Metamorphic Relation 1: 向哈希表添加一个数据后, 将哈希表转为字符串后字符串的长度会变长
     *
     * @param source_in
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
     * Metamorphic Relation 2: 在输入字符串的结尾加上注释后, 转换为JSON对象的结果不变
     *
     * @param source_in
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
     * Metamorphic Relation 3: 将哈希表中的一对键值互换, 输出的字符串长度不变
     *
     * @param source_in
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
        assertEquals(source_out.length(), follow_out.length());
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
