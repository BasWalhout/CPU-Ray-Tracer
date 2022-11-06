#include "headers/BVHNodes.h"
#include "headers/Surface.h"
#include <vector>
#include <algorithm>
#include <utility>

BVHNode::BVHNode() {}

const BoundingBox& BVHNode::getBoudingBox() {

	return this->bounds;

}

BVHNode* BVHNode::CreateNode(std::vector<Surface*> surfaces) {

	if (surfaces.size() > 1) {
		return new InternalNode(surfaces); // creates new nodes again by using this function.
	}
	else {
		if (surfaces.size() == 1) {
			return new LeafNode(**surfaces.begin());
		}
	}
	return nullptr;

}

//---------------------------------------------------------------------------------------------------------------

InternalNode::InternalNode(std::vector<Surface*> surfaces){

	if (surfaces.size() > 2) { //There are more then 2 surfaces, split the node into multiple nodes.

		this->bounds = (*surfaces.begin())->GetBoundingBox();

		for (std::vector<Surface*>::iterator surfaceIter = (surfaces.begin()+1); surfaceIter != surfaces.end(); ++surfaceIter) {
			this->bounds = this->bounds.Combine((*surfaceIter)->GetBoundingBox());
		}

		const vec3 minbound = this->bounds.GetMinBound();
		const vec3 maxbound = this->bounds.GetMaxBound();
		const vec3 diagonalSizeBounds = maxbound - minbound;

		int sortingAxis = 0;
		float largestSize = 0;

		for (int axis = 0; axis < 3; ++axis) { // Find the largest axis of the bounding box.

			if (fabsf(diagonalSizeBounds.v[axis]) > largestSize) {
				largestSize = fabsf(diagonalSizeBounds.v[axis]);
				sortingAxis = axis;
			}

		}

		float splitpoint = minbound.v[sortingAxis] + (diagonalSizeBounds.v[sortingAxis] * 0.5f);

		sortSurfacesByAxis(surfaces, sortingAxis);

		std::vector<Surface*> leftSurfaces;
		std::vector<Surface*> rightSurfaces;

		for (std::vector<Surface*>::iterator surfaceIterator = surfaces.begin(); surfaceIterator != surfaces.end(); ++surfaceIterator) {

			if ((*surfaceIterator)->GetBoundingBox().GetMidpoint().v[sortingAxis] <= splitpoint) {
				leftSurfaces.push_back((*surfaceIterator));
			}
			else {
				rightSurfaces.push_back((*surfaceIterator));
			}

		}

		if (leftSurfaces.empty() || rightSurfaces.empty()) {

			leftSurfaces.clear();
			rightSurfaces.clear();

			int midpointSurfaces = static_cast<int>(ceilf(surfaces.size() * 0.5f));
			int currentSurface = 0;

			for (std::vector<Surface*>::iterator surfaceIterator = surfaces.begin(); surfaceIterator != surfaces.end(); ++surfaceIterator) {

				++currentSurface;

				if (!(currentSurface > midpointSurfaces)) {
					leftSurfaces.push_back(*surfaceIterator);
				}
				else if (currentSurface > midpointSurfaces) {
					rightSurfaces.push_back(*surfaceIterator);
				}

			}
		}

		this->left = this->CreateNode(leftSurfaces);
		this->right = this->CreateNode(rightSurfaces);

		leftSurfaces.clear();
		rightSurfaces.clear();

	}
	else {//there are only 2 or less surfaces, make leaf nodes.

		if (surfaces.size() == 2) {
			std::vector<Surface*> leftSurfaces = { *(surfaces.begin()) };
			std::vector<Surface*> rightSurfaces = { *(surfaces.begin() + 1) };

			this->left = this->CreateNode(leftSurfaces);
			this->right = this->CreateNode(rightSurfaces);
		}
		else if (surfaces.size() == 1) {
			std::vector<Surface*> leftSurfaces = { *(surfaces.begin()) };

			this->left = this->CreateNode(leftSurfaces);
			this->right = nullptr;
		}
		else {
			this->left = this->right = nullptr;
		}
	}

}

InternalNode::~InternalNode() {

	if (left != nullptr) {
		delete left;
	}
	if (right != nullptr) {
		delete right;
	}

}

const bool InternalNode::IntersectsWithRay(const Ray& a_ray, float& a_distance, HitResult& a_result) const{

	float distance = 0.f;
	if (this->bounds.IntersectsWithRay(a_ray, distance)) {
		
		bool leftHit = false;
		float leftHitDistance = 0.f;
		HitResult leftHitResult = HitResult();

		bool rightHit = false;
		float rightHitDistance = 0.f;
		HitResult rightHitResult = HitResult();

		if (left != nullptr) {
			leftHit = left->IntersectsWithRay(a_ray, leftHitDistance, leftHitResult);
		}

		if (right != nullptr) {
			rightHit = right->IntersectsWithRay(a_ray, rightHitDistance, rightHitResult);
		}

		if ((!leftHit) && (!rightHit)) {
			a_distance = 0.f;
			return false;
		}

		else if (leftHit && rightHit) {
			if (leftHitDistance < rightHitDistance) {
				a_result = leftHitResult;
			}
			else {
				a_result = rightHitResult;
			}
		}
		else if (leftHit) {
			a_result = leftHitResult;
		}
		else if (rightHit) {
			a_result = rightHitResult;
		}
		a_distance = distance;
		return a_result.hit;
		
	}
	else { // The ray does not intersect with this node.
		a_distance = 0.f;
		return false;
	}

}

void sortSurfacesByAxis(std::vector<Surface*>& surfaces, int axis) {

	std::vector<std::pair<Surface*, float>> surfacesSortedByPositions;

	for (Surface* surface : surfaces) {
		float positionOnAxis = surface->GetBoundingBox().GetMidpoint().v[axis];
		surfacesSortedByPositions.push_back(std::make_pair(surface, positionOnAxis));
	}

	std::sort(surfacesSortedByPositions.begin(), surfacesSortedByPositions.end(), CompareByPosition);

	surfaces.clear();

	for (std::pair<Surface*, float> surface : surfacesSortedByPositions) {
		surfaces.push_back(surface.first);
	}

}

bool CompareByPosition(std::pair<Surface*, float> a, std::pair<Surface*, float> b) {

	return(a.second < b.second);

}

//---------------------------------------------------------------------------------------------------------------

LeafNode::LeafNode(const Surface& surface):
	leaf(&surface)
{
	this->bounds = leaf->GetBoundingBox();
}

const bool LeafNode::IntersectsWithRay(const Ray& a_ray, float& a_distance, HitResult& a_result) const{

	if (this->bounds.IntersectsWithRay(a_ray, a_distance)) {
		a_result = leaf->IntersectsWithRay(a_ray);
		a_distance = a_result.distance;
		return a_result.hit;
	}
	else {
		a_distance = 0.f;
		return false;
	}

}
