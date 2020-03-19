local C = {}

function C:init(unit)
  self.unit = unit
end

function C:onUpdate()
end

function C:onAppeared()
  game.fadeScreen(Color(0,0,0,1), game.ColorMode_Mul, 3, false)
end

return function(unit)
  local o = {}
  setmetatable(o, C)
  C.__index = C
  o:init(unit)
  return o
end