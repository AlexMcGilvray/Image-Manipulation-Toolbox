#pragma once
#ifndef SPACESHIP_GENERATOR_H
#define SPACESHIP_GENERATOR_H

#include "image_data.h"

struct SpaceShipGenerationParameters
{
	int width;
	int height;
};

ImageData GenerateSpaceship(struct SpaceShipGenerationParameters creationParams);

#endif