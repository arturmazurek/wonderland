//
//  Vertex.cpp
//  Wonderland
//
//  Created by Artur Mazurek on 07/02/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#include "Vertex.h"

static_assert(sizeof(Vector) == 3 * sizeof(float), "Vector structure mustn't have padding inside.");
static_assert(sizeof(Vertex) == (3 + 3 + 2) * sizeof(float), "Vertex structure mustn't have padding inside.");
