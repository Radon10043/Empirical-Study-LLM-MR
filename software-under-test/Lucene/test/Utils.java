package test;

import org.apache.lucene.document.Document;
import org.apache.lucene.document.Field;
import org.apache.lucene.analysis.Analyzer;
import org.apache.lucene.analysis.standard.StandardAnalyzer;
import org.apache.lucene.index.IndexWriter;
import org.apache.lucene.index.Term;
import org.apache.lucene.search.BooleanQuery;
import org.apache.lucene.search.Hits;
import org.apache.lucene.search.IndexSearcher;
import org.apache.lucene.search.Query;
import org.apache.lucene.search.TermQuery;
import org.apache.lucene.search.BooleanClause.Occur;
import org.apache.lucene.store.FSDirectory;

import java.io.File;
import java.io.FileReader;
import java.io.Reader;

import java.util.ArrayList;
import java.util.HashSet;

public class Utils {
    /**
     * 为要进行全文检索的文件生成索引
     *
     * @param root_path 全文检索文件夹的根目录
     * @throws Exception
     */
    public static void generateIndex(String root_path) throws Exception {
        /* @formatter:off */
        File        index_dir   = new File(root_path + File.separator + "index"); /* 索引文件夹路径 */
        File        files_dir   = new File(root_path + File.separator + "files"); /* 存储了要进行全文检索的文件的文件夹路径 */
        Analyzer    analyzer    = new StandardAnalyzer();
        IndexWriter writer      = new IndexWriter(index_dir, analyzer, true);
        File[]      files       = files_dir.listFiles();
        /* @formatter:on */

        /* 遍历要进行检索的文件, 生成索引 */
        for (int i = 0; i < files.length; i++) {
            Document document = new Document();
            Reader reader = new FileReader(files[i]);
            document.add(Field.Text("path", files[i].getCanonicalPath()));
            document.add(Field.Text("contents", reader));
            writer.addDocument(document);
        }

        writer.optimize();
        writer.close();
    }

    /**
     * 根据搜索项进行全文检索
     *
     * @param index_dir    索引文件所在目录
     * @param search_terms 搜索项
     * @return 符合搜索项的所有文件的路径
     * @throws Exception
     */
    public static ArrayList<String> fullTextSearch(String index_dir, ArrayList<String> search_terms) throws Exception {

        /* @formatter:off */
        FSDirectory         directory = FSDirectory.getDirectory(new File(index_dir), false);
        IndexSearcher       searcher = new IndexSearcher(directory);
        BooleanQuery        query       = new BooleanQuery();
        HashSet<String>     keywords    = new HashSet<String>();
        /* @formatter:on */

        /* 向HashSet中添加关键词 */
        keywords.add("AND");
        keywords.add("OR");
        keywords.add("NOT");

        /* 根据搜索项内容的不同生成不通过的query */
        switch (search_terms.size()) {

            case 1: {
                /* 搜索项只有1个时, 寻找出现该搜索项的文件 */
                if (!keywords.contains(search_terms.get(0))) {
                    Query q = new TermQuery(new Term("contents", search_terms.get(0)));
                    query.add(q, Occur.MUST);
                }
                break;
            }

            case 2: {
                /*
                 * 搜索项有2个时, 如果第2个搜索项是关键字, 那么就只搜索出现第1个搜索项的文件,
                 * 如果第2个搜索项不是关键字, 那么搜索2个搜索项都出现的文件.
                 */
                if (keywords.contains(search_terms.get(1))) {
                    Query q = new TermQuery(new Term("contents", search_terms.get(0)));
                    query.add(q, Occur.MUST);
                } else {
                    Query q = new TermQuery(new Term("contents", search_terms.get(0) + search_terms.get(1)));
                    query.add(q, Occur.MUST);
                }
                break;
            }

            case 3: {
                /*
                 * 搜索项有3个时, 分为4种情况:
                 * 1. 中间是AND: 搜索左右两侧的搜索项都出现的文件
                 * 2. 中间是OR: 搜索左侧或右侧搜索项出现的文件
                 * 3. 中间是NOT: 搜索左侧搜索项出现但右侧搜索项没出现的文件
                 * 4. 中间不是关键字: 搜索3个搜索项都出现的文件
                 */
                if (search_terms.get(1).equals("AND")) {
                    Query q1 = new TermQuery(new Term("contents", search_terms.get(0)));
                    Query q2 = new TermQuery(new Term("contents", search_terms.get(2)));
                    query.add(q1, Occur.MUST);
                    query.add(q2, Occur.MUST);
                } else if (search_terms.get(1).equals("OR")) {
                    Query q1 = new TermQuery(new Term("contents", search_terms.get(0)));
                    Query q2 = new TermQuery(new Term("contents", search_terms.get(2)));
                    query.add(q1, Occur.SHOULD);
                    query.add(q2, Occur.SHOULD);
                } else if (search_terms.get(1).equals("NOT")) {
                    Query q1 = new TermQuery(new Term("contents", search_terms.get(0)));
                    Query q2 = new TermQuery(new Term("contents", search_terms.get(2)));
                    query.add(q1, Occur.MUST);
                    query.add(q2, Occur.MUST_NOT);
                } else {
                    Query q1 = new TermQuery(new Term("contents", search_terms.get(0)));
                    Query q2 = new TermQuery(new Term("contents", search_terms.get(1)));
                    Query q3 = new TermQuery(new Term("contents", search_terms.get(2)));
                    query.add(q1, Occur.MUST);
                    query.add(q2, Occur.MUST);
                    query.add(q3, Occur.MUST);
                }
                break;
            }

        }

        /* 寻找与搜索项匹配的文件, 并将路径存入result */
        Hits hits = searcher.search(query);
        ArrayList<String> result = new ArrayList<String>();
        for (int i = 0; i < hits.length(); i++) {
            result.add(hits.doc(i).get("path"));
        }

        /* 返回所有符合搜索项的文件的路径 */
        return result;

    }
}
