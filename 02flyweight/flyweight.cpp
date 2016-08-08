/*
 * The pattern solves that by separating out an object’s data into two kinds. 
 * The first kind of data is the stuff that’s not specific to a single instance of that object 
 * and can be shared across all of them.  
 * The rest of the data is the extrinsic state, the stuff that is unique to that instance. 
 * */

/* 
 * sample01: 在游戏地图上绘制一千棵树
 * */ 

// version 01
class Tree
{
    private:
        Mesh mesh_; // 网格
        Texture bark_;// 树枝
        Texture leaves_;// 树叶

        Vextor position_;// 位置
        double height_;// 高度
        double thickness_;// 密度
        Color barkTint_;// 树干颜色
        Color leafTint_;// 叶子颜色
};

// version 02
// 提取共有的数据
class TreeModel
{
    private:
        Mesh mesh_; // 网格
        Texture bark_;// 树枝
        Texture leaves_;// 树叶
};

class Tree
{
    private:
        TreeModel* model;

        Vextor position_;// 位置
        double height_;// 高度
        double thickness_;// 密度
        Color barkTint_;// 树干颜色
        Color leafTint_;// 叶子颜色
};

/* 
 * sample02: 游戏地形 
 * */ 

// version 01
enum Terrain
{
    TERRAIN_GRASS, // 草地
    TERRAIN_HILL, // 丘陵
    TERRAIN_RIVER // 河流
};

class World
{
    public:
        int getMovementCost(int x, int y){
            switch(tiles_[x][y]) {
                case TERRAIN_GRASS:
                    return 1;
                case TERRAIN_HILL:
                    return 2;
                cass TERRAIN_RIVER:
                    return 3;
            }   
        }

        bool isWater(int x, int y) {
            switch(tiles_[x][y]) {
                case TERRAIN_GRASS:
                    return false;
                case TERRAIN_HILL:
                    return false;
                cass TERRAIN_RIVER:
                    return true;
            }   
        }

    private:
        Terrain titles_[WIDTH][HEIGHT];
};

// version 02
class Terrain
{
    public:
        Terrain(int movementCost, bool isWater, Texture texture):
            movementCost_(movementCost), isWater_(isWater), texture_(texture) {}

        int getMovementCost() const {
            return movementCost_;
        }

        bool isWater() const {
            return isWater_; 
        }

        const Texture& getTexture() const {
            return texture_;
        }
    private:
        int movementCost_;
        bool isWater_;
        Texture texture_;
};

class World
{
    public:
        World():
            grassTerrain_(1, false, GRASS_TEXTURE),
            hillTerrain_(2, false, HILL_TEXTURE),
            riverTerrain_(3, true, RIVER_TEXTURE) {}

        void generateTerrain() {
            // Fill the ground with grass
            for (int x =0; x < WIDTH; x++) {
                for (int y = 0; y < HEIGHT; y++) {
                    if (random(10) == 0) {
                        tiles_[x][y] = &hillTerrain_;
                    else {
                        tiles_[x][y] = &riverTerrian_;
                    }
                }
            }
            // Lay a river
            int x = random(WIDTH);
            for (int y = 0; y < HEIGHT; y ++) {
                tiles_[x][y] = &riverTerrian_;
            }
        }

        const Terrain& getTile(int x, int y) const {
            return *tiles_[x][y];
        }
        
    private:
        Terrain grassTerrain_;
        Terrain hillTerrain_;
        Terrain riverTerrian_;
};

