// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include <Metal/Metal.h>

#include <memory>
#include <string>

#include "flutter/fml/macros.h"
#include "flutter/impeller/impeller/compositor/shader_types.h"

namespace impeller {

class Context;

class ShaderFunction {
 public:
  ~ShaderFunction();

  ShaderStage GetStage() const;

 private:
  friend class ShaderLibrary;

  id<MTLFunction> function_ = nullptr;
  ShaderStage stage_;

  ShaderFunction(id<MTLFunction> function, ShaderStage stage);

  FML_DISALLOW_COPY_AND_ASSIGN(ShaderFunction);
};

class ShaderLibrary {
 public:
  ~ShaderLibrary();

  std::shared_ptr<ShaderFunction> GetFunction(const std::string& name,
                                              ShaderStage stage);

 private:
  friend class Context;

  id<MTLLibrary> library_ = nullptr;

  ShaderLibrary(id<MTLLibrary> library);

  FML_DISALLOW_COPY_AND_ASSIGN(ShaderLibrary);
};

}  // namespace impeller