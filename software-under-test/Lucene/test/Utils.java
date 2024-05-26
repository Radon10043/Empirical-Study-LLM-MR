package test;

import org.apache.lucene.document.Document;
import org.apache.lucene.document.Field;
import org.apache.lucene.analysis.Analyzer;
import org.apache.lucene.analysis.standard.StandardAnalyzer;
import org.apache.lucene.index.IndexWriter;
import org.apache.lucene.queryParser.QueryParser;
import org.apache.lucene.search.Hits;
import org.apache.lucene.search.IndexSearcher;
import org.apache.lucene.search.Query;
import org.apache.lucene.store.FSDirectory;

import java.io.File;
import java.io.FileReader;
import java.io.Reader;

import java.util.ArrayList;

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
        /* 将搜索项转换为String对象 */
        String s = "";
        for (String term : search_terms) {
            s += term + " ";
        }
        return fullTextSearch(index_dir, s);
    }

    /**
     * 根据搜索项进行全文检索
     * 
     * @param index_dir    索引文件所在目录
     * @param search_terms 搜索项
     * @return 符合搜索项的所有文件的路径
     * @throws Exception
     */
    public static ArrayList<String> fullTextSearch(String index_dir, String search_terms) throws Exception {
        /* @formatter:off */
        FSDirectory     directory   = FSDirectory.getDirectory(new File(index_dir), false);
        IndexSearcher   searcher    = new IndexSearcher(directory);
        QueryParser     parser      = new QueryParser("contents", new StandardAnalyzer());
        /* @formatter:on */

        /* 将搜索项转换为Query对象 */
        Query query = parser.parse(search_terms);

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
