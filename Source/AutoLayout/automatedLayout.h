#pragma once

#include "layoutConstrains.h"

#include <queue>
#include <random>
#include <fstream>
#include <chrono>


using namespace cv;

class automatedLayout
{
private:
	layoutConstrains *constrains;
	Room * room;
	vector<float>weights;
	float cost_function();
	float density_function(float cost);
	void randomly_perturb(vector<Vec3f>& ori_trans, vector<float>& ori_rot, vector<int>& selectedid);
	void Metropolis_Hastings();
	void random_translation(int furnitureID, default_random_engine generator);

public:
	
	int resNum = 3;
	float min_cost;
	queue<vector<Vec3f>> res_transform;
	queue<vector<float>> res_rotation;
	

	automatedLayout(Room* m_room, vector<float>in_weights) {
		constrains = new layoutConstrains(m_room);
		room = m_room;
		min_cost = INFINITY;
		weights = in_weights;
		res_transform.push(m_room->get_objs_transformation());
		res_rotation.push(m_room->get_objs_rotation());

	}
	automatedLayout() {
		constrains = new layoutConstrains(room);
		min_cost = INFINITY;
		res_transform.push(room->get_objs_transformation());
		res_rotation.push(room->get_objs_rotation());
	}
	void generate_suggestions();
	void display_suggestions();
};

