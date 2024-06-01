package top.ivicel.ch06;


import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

/**
 * 基于数组实现的 hash map, hash 函数使用 mod n 方法
 */
public class ArrayHashMap {

    private final List<Pair> buckets;


    public ArrayHashMap() {
        // 初始化 100 个桶
        buckets = new ArrayList<>();
        for (int i = 0; i < 100; i++) {
            buckets.add(null);
        }
    }


    /**
     * hash 函数，使用 mod 100 方法
     */
    private int hashFunc(int key) {
        return key % 100;
    }

    public String get(int key) {
        int index = hashFunc(key);
        Pair pair = buckets.get(index);
        return pair == null ? null : pair.val;
    }

    public void put(int key, String val) {
        Pair pair = new Pair(key, val);
        int index = hashFunc(key);
        // 并不处理冲突
        buckets.set(index, pair);
    }

    public void remove(int key) {
        int index = hashFunc(key);
        // 设置为 null, 表示删除
        buckets.set(index, null);
    }

    public List<Integer> keySet() {
        return buckets.stream().filter(Objects::nonNull).map(pair -> pair.key).toList();
    }

    public List<String> valueSet() {
        return buckets.stream().filter(Objects::nonNull).map(pair -> pair.val).toList();
    }

    public List<Pair> pairSet() {
        return buckets.stream().filter(Objects::nonNull).toList();
    }

    public void print() {
        for (Pair kv : pairSet()) {
            System.out.println(kv.key + " -> " + kv.val);
        }
    }

    /**
     * 键值对
     */
    public static class Pair {
        public int key;

        public String val;

        public Pair(int key, String val) {
            this.key = key;
            this.val = val;
        }
    }
}
