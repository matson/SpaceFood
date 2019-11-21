//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//
// "Creature Box" -- flocking app
//
// by Christopher Rasmussen
//
// CISC 440/640, March, 2014
// updated to OpenGL 3.3, March, 2016
//
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
#define _USE_MATH_DEFINES
#include "Predator.hh"

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

extern vector <Flocker *> flocker_array;
vector <Predator*> predator_array;
int predator_history_length = 30;
int predator_draw_mode = DRAW_MODE_POLY_PREDATOR;
extern glm::mat4 ViewMat;
extern glm::mat4 ProjectionMat;

extern GLuint ModelMatrixID;
extern GLuint ViewMatrixID;
extern GLuint MatrixID;
glm::vec3 hunger_force;

#define M_PI 3.14159

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

Predator::Predator(int _index,
	double init_x, double init_y, double init_z,
	double init_vx, double init_vy, double init_vz,
	double rand_force_limit,
	double min_hungery_distance, double max_hungery_distance, double hunger_mass,
	float r, float g, float b,
	int max_hist) : Creature(_index, init_x, init_y, init_z, init_vx, init_vy, init_vz, r, g, b, max_hist)


{ 
	random_force_limit = rand_force_limit;
	//hungry stuff
	max_hunger_distance = max_hungery_distance;
	min_hunger_distance = min_hungery_distance;
	hunger_weight = hunger_mass;
	max_squared_hunger_distance = max_hunger_distance * max_hunger_distance; //product
	min_squared_hunger_distance = min_hunger_distance * min_hunger_distance;
	
	//separation_weight = separate_weight;
	inv_range_squared_hungry_distance = 1.0 / (max_squared_hunger_distance - min_squared_hunger_distance);
	
	//no need for cohesion (group) forces
	
}

//----------------------------------------------------------------------------

void Predator::draw(glm::mat4 Model)
{
	//begin code here
	int draw_mode, num_vertices;

	GLfloat *vertex_buffer_data;
	GLfloat *color_buffer_data;


			num_vertices = 12;
			draw_mode = GL_TRIANGLES;

			vertex_buffer_data = (GLfloat *)malloc(3 * num_vertices * sizeof(GLfloat));
			color_buffer_data = (GLfloat *)malloc(3 * num_vertices * sizeof(GLfloat));

			double width = 0.9f;
			double height = 0.9f;
			double length = 1.3f;

			// horizontal

			vertex_buffer_data[0] = position.x - 0.5f * width * frame_x.x;
			vertex_buffer_data[1] = position.y - 0.5f * width * frame_x.y;
			vertex_buffer_data[2] = position.z - 0.5f * width * frame_x.z;

			vertex_buffer_data[3] = position.x - 0.8f * length * frame_z.x;
			vertex_buffer_data[4] = position.y - 0.8f * length * frame_z.y;
			vertex_buffer_data[5] = position.z - 0.8f * length * frame_z.z;

			vertex_buffer_data[6] = position.x + 0.2f * length * frame_z.x;
			vertex_buffer_data[7] = position.y + 0.2f * length * frame_z.y;
			vertex_buffer_data[8] = position.z + 0.2f * length * frame_z.z;


			vertex_buffer_data[9] = position.x + 0.5f * width * frame_x.x;
			vertex_buffer_data[10] = position.y + 0.5f * width * frame_x.y;
			vertex_buffer_data[11] = position.z + 0.5f * width * frame_x.z;

			vertex_buffer_data[12] = position.x + 0.2f * length * frame_z.x;
			vertex_buffer_data[13] = position.y + 0.2f * length * frame_z.y;
			vertex_buffer_data[14] = position.z + 0.2f * length * frame_z.z;

			vertex_buffer_data[15] = position.x - 0.8f * length * frame_z.x;
			vertex_buffer_data[16] = position.y - 0.8f * length * frame_z.y;
			vertex_buffer_data[17] = position.z - 0.8f * length * frame_z.z;

			// vertical

			vertex_buffer_data[18] = position.x + 0.5f * height * frame_y.x;
			vertex_buffer_data[19] = position.y + 0.5f * height * frame_y.y;
			vertex_buffer_data[20] = position.z + 0.5f * height * frame_y.z;

			vertex_buffer_data[21] = position.x - 0.8f * length * frame_z.x;
			vertex_buffer_data[22] = position.y - 0.8f * length * frame_z.y;
			vertex_buffer_data[23] = position.z - 0.8f * length * frame_z.z;

			vertex_buffer_data[24] = position.x + 0.2f * length * frame_z.x;
			vertex_buffer_data[25] = position.y + 0.2f * length * frame_z.y;
			vertex_buffer_data[26] = position.z + 0.2f * length * frame_z.z;


			vertex_buffer_data[27] = position.x - 0.5f * height * frame_y.x;
			vertex_buffer_data[28] = position.y - 0.5f * height * frame_y.y;
			vertex_buffer_data[29] = position.z - 0.5f * height * frame_y.z;

			vertex_buffer_data[30] = position.x + 0.2f * length * frame_z.x;
			vertex_buffer_data[31] = position.y + 0.2f * length * frame_z.y;
			vertex_buffer_data[32] = position.z + 0.2f * length * frame_z.z;

			vertex_buffer_data[33] = position.x - 0.8f * length * frame_z.x;
			vertex_buffer_data[34] = position.y - 0.8f * length * frame_z.y;
			vertex_buffer_data[35] = position.z - 0.8f * length * frame_z.z;

			// color

			int i;

			for (i = 0; i < 6; i++) {
				color_buffer_data[3 * i] = 1.0f;
				color_buffer_data[3 * i + 1] = 0.0f;
				color_buffer_data[3 * i + 2] = 1.0f;
			}

			for (i = 6; i < 9; i++) {
				color_buffer_data[3 * i] = 1.0f;
				color_buffer_data[3 * i + 1] = 1.0f;
				color_buffer_data[3 * i + 2] = 0.0f;
			}

			for (i = 9; i < 12; i++) {
				color_buffer_data[3 * i] = 0.5f;
				color_buffer_data[3 * i + 1] = 0.5f;
				color_buffer_data[3 * i + 2] = 0.0f;
			}
		

		// Our ModelViewProjection : multiplication of our 3 matrices

		glm::mat4 MVP = ProjectionMat * ViewMat * Model;

		// make this transform available to shaders  

		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

		// 1st attribute buffer : vertices

		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glBufferData(GL_ARRAY_BUFFER, 3 * num_vertices * sizeof(GLfloat), vertex_buffer_data, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(0,                  // attribute. 0 to match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// 2nd attribute buffer : colors

		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
		glBufferData(GL_ARRAY_BUFFER, 3 * num_vertices * sizeof(GLfloat), color_buffer_data, GL_STATIC_DRAW);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
		glVertexAttribPointer(1,                                // attribute. 1 to match the layout in the shader.
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		// Draw the predator!

		glDrawArrays(draw_mode, 0, num_vertices);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		free(vertex_buffer_data);
		free(color_buffer_data);

	
}

bool Predator::compute_hungry_force()
{
	//calculate the lowest distance from the predator to the flocker and set it to move in that direction
	int i, j;
	double F, percent;
	glm::vec3 cookie;
	double ghost;
	glm::vec3 minDist;
	glm::vec3 minDistPos;
	double minLow;
	glm::vec3 direction;

	//define vector first (direction needed)
	hunger_force = glm::vec3(0, 0, 0);
	//Go through all distances of flockers.
	for (i = 0; i < flocker_array.size(); i++) {
		cookie = flocker_array[i]->position - position;
		ghost = glm::length2(cookie);
		if (i == 0) {
			minDist = flocker_array[i]->position - position;
			minDistPos = flocker_array[i]->position;
			minLow = glm::length2(minDist);
		}
		else {
			if (ghost > minLow) {
				minDist = cookie;
				minDistPos = flocker_array[i]->position;
				minLow = glm::length2(minDist);
			}
		}
	}
	//prevent wonkiness
	percent = (minLow - max_squared_hunger_distance) * inv_range_squared_hungry_distance;
	F = 0.5 + -0.5 * cos(percent * 2.0 * M_PI);
	direction = (float)F * glm::normalize(minDist);
	hunger_force += direction;
	if (minLow == NULL) {
		hunger_force *= (float)hunger_weight;
		return true;
	}
	else {
		return false;
	}

}

//----------------------------------------------------------------------------

// based on:
// http://processing.org/examples/flocking
// http://libcinder.org/docs/dev/flocking_chapter4.html

// side effect is putting values into ALIGNMENT_FORCE vector

//----------------------------------------------------------------------------


//need to finish update function in order to have it show in the box
void Predator::update()
{
	
	//set acceleration 
	acceleration = glm::vec3(0, 0, 0);

	//behaviors
	compute_hungry_force();
	acceleration += hunger_force;

	draw_color.r = glm::length(hunger_force);
	if (draw_color.r > 0) {
		draw_color = glm::normalize(draw_color);
	}
	else {
		draw_color = base_color;
	}

	// randomness

	if (random_force_limit > 0.0) {
		acceleration.x += uniform_random(-random_force_limit, random_force_limit);
		acceleration.y += uniform_random(-random_force_limit, random_force_limit);
		acceleration.z += uniform_random(-random_force_limit, random_force_limit);
	}


	// update velocity

	new_velocity = velocity + acceleration;   // scale acceleration by dt?

  // limit velocity

	double mag = glm::length(new_velocity);
	if (mag > MAX_FLOCKER_SPEED)
		new_velocity *= (float)(MAX_FLOCKER_SPEED / mag);

	// update position

	new_position = position + new_velocity;   // scale new_velocity by dt?
}

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/*
	//
	double random_force_limit = 0.6;
	acceleration = glm::vec3(0, 0, 0);
	glm::vec3 separation_force = glm::vec3(0, 0, 0);
	glm::vec3 alignment_force = glm::vec3(0, 0, 0);
	glm::vec3 cohesion_force = glm::vec3(0, 0, 0);
	//compute_separation_force();


	acceleration += 0;// separation_force;

	//compute_alignment_force();
	acceleration += 0;// alignment_force;

	//compute_cohesion_force();
	acceleration += 0;// cohesion_force;



	// randomness

	if (random_force_limit > 0.0) {
		acceleration.x += uniform_random(-random_force_limit, random_force_limit);
		acceleration.y += uniform_random(-random_force_limit, random_force_limit);
		acceleration.z += uniform_random(-random_force_limit, random_force_limit);
	}

	// update velocity

	new_velocity = velocity + acceleration;   // scale acceleration by dt?

	// limit velocity

	double mag = glm::length(new_velocity);
	if (mag > MAX_FLOCKER_SPEED)
		new_velocity *= (float)(MAX_FLOCKER_SPEED / mag);

	// update position

	new_position = position + new_velocity;








*/