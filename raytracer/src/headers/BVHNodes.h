#pragma once
#include <vector>
#include "BoundingBox.h"

class Ray;
struct HitResult;
class Surface;

class BVHNode {

public:

	virtual const bool IntersectsWithRay(const Ray& a_ray, float& a_distance, HitResult& a_result) const =0;
	BVHNode* CreateNode(std::vector<Surface*> surfaces);
	const BoundingBox& getBoudingBox();

protected:

	BVHNode();
	BoundingBox bounds;

};

//---------------------------------------------------------------------------------------------------------------

class InternalNode : public BVHNode {

public:

	~InternalNode();

	InternalNode(std::vector<Surface*> surfaces);
	const bool IntersectsWithRay(const Ray& a_ray, float& a_distance, HitResult& a_result) const override;

private:

	BVHNode* left;
	BVHNode* right;

};

void sortSurfacesByAxis(std::vector<Surface*>& surfaces, int axis);
bool CompareByPosition(std::pair<Surface*, float> a, std::pair<Surface*, float> b);

//---------------------------------------------------------------------------------------------------------------

class LeafNode : public BVHNode {

public:

	LeafNode(const Surface& surface);
	const bool IntersectsWithRay(const Ray& a_ray, float& a_distance, HitResult& a_result) const override;

private:

	const Surface* leaf;

};