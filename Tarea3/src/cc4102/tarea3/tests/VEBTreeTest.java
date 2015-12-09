package cc4102.tarea3.tests;

import cc4102.tarea3.olguin_romero.VEBTree;

import static org.junit.Assert.*;

/**
 * Created by arachnid92 on 09-12-15.
 */
public class VEBTreeTest extends TreeTest {

    @Override
    public void setUp() throws Exception {
        this.tree = new VEBTree((int) Math.pow(2, 16));
        populate();
    }
}