#include "RisingTides.h"
#include "GUI/SimpleTest.h"
#include "queue.h"
using namespace std;

/*
这道题用DFS和BFS都可以.测试案例都能过.但是在执行大型图的时候,DFS会栈溢出.BFS 和 DFS的空间复杂度
都是O(n^2)
*/

/* 解决方案1 DFS 测试案例可以通过,但是在执行大型图的时候仍然会栈溢出导致程序终止 */

// #define UNKNOWEN -1
// #define FLOODED 1
// #define NOT_FLOODED 0

// //用于探索上下左右的辅助数组
// const int directionsHelp[5]={-1,0,1,0,-1};

// void dfs(const Grid<double>& terrain,const GridLocation & source,double height,Grid< int > & isFlooded){
//     int sourceRow = source.row;
//     int sourceCol = source.col;

//     //此水位已经探索过
//     if(isFlooded[sourceRow][sourceCol]!=UNKNOWEN){
//         return;
//     }

//     isFlooded[sourceRow][sourceCol]= terrain[sourceRow][sourceCol]<=height?FLOODED:NOT_FLOODED;

//     //只有它被淹没,才有向四方扩展的必要性
//     if(isFlooded[sourceRow][sourceCol]==FLOODED){
//         int boundRow =terrain.numRows();
//         int boundCol = terrain.numCols();

//         //分别是上 右 下 左
//         for(int i=0;i<4;i++){
//             int nextRow = sourceRow + directionsHelp[i];
//             int nextCol = sourceCol + directionsHelp[i+1];


//             //(nextRow,nextCol)合法
//             if(0<= nextRow && nextRow<boundRow && 0<= nextCol && nextCol<boundCol){
//                 GridLocation loc = {nextRow,nextCol};
//                 dfs(terrain,loc,height,isFlooded);
//             }
//         }
//     }


// }


// Grid<bool> floodedRegionsIn(const Grid<double>& terrain,
//                             const Vector<GridLocation>& sources,
//                             double height) {
//     int rows = terrain.numRows();
//     int cols = terrain.numCols();
//     //isFlood设置类型为int,-1表示不知道,1表示会淹没,0表示不会淹没
//     Grid< int >  isFlooded ( rows ,  cols );
//     for(int i=0;i<rows;i++){
//         for(int j=0;j<cols;j++){
//             isFlooded[i][j]=UNKNOWEN;//初始化均为-1,表示不知道
//         }
//     }

//     for(GridLocation  loc: sources){
//         dfs(terrain,loc,height,isFlooded);
//     }

//     Grid< bool >  ans ( rows ,  cols );
//     for(int i=0;i<rows;i++){
//         for(int j=0;j<cols;j++){
//             ans[i][j]=isFlooded[i][j]==FLOODED;//仅当FlOODED为true,其他UNKONWEN或NOT_FLOODED为false
//         }
//     }
//     return ans;
// }


/* 解决方案2 BFS */

#define UNKNOWEN -1
#define FLOODED 1
#define NOT_FLOODED 0

//用于探索上下左右的辅助数组
const int directionsHelp[5]={-1,0,1,0,-1};


Grid<bool> floodedRegionsIn(const Grid<double>& terrain,
                            const Vector<GridLocation>& sources,
                            double height) {
    int rows = terrain.numRows();
    int cols = terrain.numCols();
    //isFlood设置类型为int,-1表示不知道,1表示会淹没,0表示不会淹没
    Grid< int >  isFlooded ( rows ,  cols );
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            isFlooded[i][j]=UNKNOWEN;//初始化均为-1,表示不知道
        }
    }

    //入队
    Queue< GridLocation >  queue ;
    for(GridLocation  loc: sources){
        queue.enqueue(loc);
    }

    while(!queue.isEmpty()){
        GridLocation  loc = queue.dequeue();
        int curRow = loc.row;
        int curCol = loc.col;
        //该位置没有探索过
        if(isFlooded[curRow][curCol]==UNKNOWEN){
            isFlooded[curRow][curCol]= terrain[curRow][curCol]<=height?FLOODED:NOT_FLOODED;

            //只有它被淹没,才有向四方扩展的必要性
            if(isFlooded[curRow][curCol]==FLOODED){
                //分别是上 右 下 左
                for(int i=0;i<4;i++){
                    int nextRow = curRow + directionsHelp[i];
                    int nextCol = curCol + directionsHelp[i+1];

                    //(nextRow,nextCol)合法 且 未知
                    if(0<= nextRow && nextRow<rows && 0<= nextCol && nextCol<cols &&
                        isFlooded[nextRow][nextCol]==UNKNOWEN){
                        GridLocation loc = {nextRow,nextCol};
                        queue.enqueue(loc);
                    }
                }
            }
        }
    }

    Grid< bool >  ans ( rows ,  cols );
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            ans[i][j]=isFlooded[i][j]==FLOODED;//仅当FlOODED为true,其他UNKONWEN或NOT_FLOODED为false
        }
    }
    return ans;
}

/***** Test Cases Below This Point *****/
PROVIDED_TEST("Nothing gets wet if there are no water sources.") {
    Grid<double> world = {
        { 0, 0, 0 },
        { 0, 0, 0 },
        { 0, 0, 0 }
    };

    Vector<GridLocation> sources = {
        // empty
    };

    /* There are no water sources, so nothing should be underwater. */
    Grid<bool> water = floodedRegionsIn(world, sources, 1.0);
    Grid<bool> expected = {
        { false, false, false },
        { false, false, false },
        { false, false, false }
    };

    EXPECT_EQUAL(water, expected);
}

PROVIDED_TEST("Everything gets wet if all locations are below the water level.") {
    Grid<double> world = {
        { 0, 0, 0 },
        { 0, 0, 0 },
        { 0, 0, 0 }
    };

    Vector<GridLocation> sources = {
        { 0, 0 }
    };

    /* Everything should flood; there are no barriers to stop the water. */
    Grid<bool> water = floodedRegionsIn(world, sources, 1.0);
    Grid<bool> expected = {
        {  true,  true,  true },
        {  true,  true,  true },
        {  true,  true,  true }
    };

    EXPECT_EQUAL(water, expected);
}

PROVIDED_TEST("Water can't cross a vertical levee.") {
    Grid<double> world = {
        { 0, 2, 0 },
        { 0, 2, 0 },
        { 0, 2, 0 }
    };

    Vector<GridLocation> sources = {
        { 0, 0 }
    };

    /* Only locations to the left of the barrier should be under water. */
    Grid<bool> water = floodedRegionsIn(world, sources, 1.0);
    Grid<bool> expected = {
        {  true, false, false },
        {  true, false, false },
        {  true, false, false }
    };

    EXPECT_EQUAL(water, expected);
}

PROVIDED_TEST("Water can't cross a diagonal levee.") {
    Grid<double> world = {
        { 0, 0, 2 },
        { 0, 2, 0 },
        { 2, 0, 0 }
    };

    Vector<GridLocation> sources = {
        { 0, 0 }
    };

    /* Water only flows in the four cardinal directions, so it can't
     * pass through the barrier. Only the top should be flooded.
     */
    Grid<bool> water = floodedRegionsIn(world, sources, 1.0);
    Grid<bool> expected = {
        {  true,  true, false },
        {  true, false, false },
        { false, false, false }
    };

    EXPECT_EQUAL(water, expected);
}

PROVIDED_TEST("Water can't flow diagonally.") {
    Grid<double> world = {
        { 0, 2, 0 },
        { 2, 0, 2 },
        { 0, 2, 0 }
    };

    Vector<GridLocation> sources = {
        { 1, 1 }
    };

    /* Water should be trapped in the center, since it can't move
     * diagonally.
     */
    Grid<bool> water = floodedRegionsIn(world, sources, 1.0);
    Grid<bool> expected = {
        { false, false, false },
        { false,  true, false },
        { false, false, false }
    };

    EXPECT_EQUAL(water, expected);
}

PROVIDED_TEST("Water can flow in all cardinal directions.") {
    Grid<double> world = {
        { 2, 0, 2 },
        { 0, 0, 0 },
        { 2, 0, 2 }
    };

    Vector<GridLocation> sources = {
        { 1, 1 }
    };

    /* The water in this case should flow up, down, left, and right. */
    Grid<bool> water = floodedRegionsIn(world, sources, 1.0);
    Grid<bool> expected = {
        { false,  true, false },
        {  true,  true,  true },
        { false,  true, false }
    };

    EXPECT_EQUAL(water, expected);
}

PROVIDED_TEST("Water can flow from multiple sources.") {
    Grid<double> world = {
        { 0, 0, 2 },
        { 0, 2, 0 },
        { 2, 0, 0 }
    };

    Vector<GridLocation> sources = {
        { 0, 0 },
        { 2, 2 }
    };

    /* Everything except the levee should be under water. */
    Grid<bool> water = floodedRegionsIn(world, sources, 1.0);
    Grid<bool> expected = {
        {  true,  true, false },
        {  true, false,  true },
        { false,  true,  true }
    };

    EXPECT_EQUAL(water, expected);
}

PROVIDED_TEST("Handles asymmetric worlds and non-square grids") {
    Grid<double> world = {
        { 3, 1, 4, 1 },
        { 5, 9, 2, 6 },
        { 5, 3, 5, 8 }
    };

    /* Initial test - water shouldn't leak out from the 2 if the height is 3.5. */
    Vector<GridLocation> sources = {
        { 1, 2 }
    };

    Grid<bool> expected = {
        { false, false, false, false },
        { false, false,  true, false },
        { false, false, false, false },
    };

    EXPECT_EQUAL(floodedRegionsIn(world, sources, 3.5), expected);

    /* Now, increase the water height to 4.5. */
    expected = {
        {  true,  true,  true,  true },
        { false, false,  true, false },
        { false, false, false, false },
    };

    EXPECT_EQUAL(floodedRegionsIn(world, sources, 4.5), expected);

    /* Now, increase the water height to 5.5. */
    expected = {
        {  true,  true,  true,  true },
        {  true, false,  true, false },
        {  true,  true,  true, false },
    };

    EXPECT_EQUAL(floodedRegionsIn(world, sources, 5.5), expected);

    /* Now, increase the water height to 6.5. */
    expected = {
        {  true,  true,  true,  true },
        {  true, false,  true,  true },
        {  true,  true,  true, false },
    };

    EXPECT_EQUAL(floodedRegionsIn(world, sources, 6.5), expected);

    /* Now, increase the water height to 9.5. */
    expected = {
        {  true,  true,  true,  true },
        {  true,  true,  true,  true },
        {  true,  true,  true,  true },
    };

    EXPECT_EQUAL(floodedRegionsIn(world, sources, 9.5), expected);
}

PROVIDED_TEST("Stress test: Handles a large, empty world quickly.") {
    Grid<double> world(100, 100); // Large world, everything defaults to 0 height.
    Vector<GridLocation> sources = {
        { 0, 0 }
    };

    /* This may take a long time to complete if the solution is inefficient. Look
     * for things like
     *
     * 1. passing around large objects by *value* rather than by *reference*,
     * 2. revisiting the same squares multiple times (e.g. flooding the same
     *    cell many times due to not checking if something is flooded),
     *
     * etc.
     */
    Grid<bool> water = floodedRegionsIn(world, sources, 1.0);
    EXPECT_EQUAL(water.numRows(), world.numRows());
    EXPECT_EQUAL(water.numCols(), world.numCols());

    /* Everything should be flooded. */
    for (int row = 0; row < world.numRows(); row++) {
        for (int col = 0; col < world.numCols(); col++) {
            EXPECT_EQUAL(water[row][col], true);
        }
    }
}
