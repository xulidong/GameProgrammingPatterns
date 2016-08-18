/*
 *  将工作延期至需要其结果时才去执行，避免不必要的工作。
 * */

// version 01

class Transform
{
public:
	static Transform origin();

	Transform combine(Transform& other);
};

class GraphNode
{
public:
	GraphNode(Mesh* mesh) : mesh_(mesh), local_(Transform::origin())
	{}

private:
	Transform local_;
	Mesh* mesh_;

	GraphNode* children_[MAX_CHILDREN];
	int numChildren_;
};

void GraphNode::render(Transform parentWorld)
{
	Transform world = local_.combine(parentWorld);

	if (mesh_) renderMesh(mesh_, world);

	for (int i = 0; i < numChildren_; i++)
	{
		children_[i]->render(world);
	}
}

GraphNode* graph_ = new GraphNode(NULL);
graph_->render(Transform::origin());


// version 02

class GraphNode
{
public:
	GraphNode(Mesh* mesh) : mesh_(mesh), local_(Transform::origin()), dirty_(true)
	{}

	void setTransform(Transform local)
	{
		local_ = local;
		dirty_ = true;
	}

private:
	Transform world_;
	bool dirty_;
	// Other fields...
};

void GraphNode::render(Transform parentWorld, bool dirty)
{
	dirty |= dirty_;
	if (dirty) {
		world_ = local_.combine(parentWorld);
		dirty_ = false;
	}

	if (mesh_) 
		renderMesh(mesh_, world_);

	for (int i = 0; i < numChildren_; i++) {
		children_[i]->render(world_, dirty);
	}
}