
local JSON = assert(loadfile "LuaScripts/json.lua")()
local keys = assert(loadfile "LuaScripts/keycode.lua")()

local mi_clase = {}

mi_clase["instantiate"] = function (params)
    p = JSON:decode(params)
    local self = {}
    self.hp = p.hp
    self.name = p.name
    self.rb = nil
    return self
end

mi_clase["start"] = function (_self, lua)
    --local p = lua:instantiate("penguin2")
    --local pRB = lua:getRigidbody(p)
    --pRB:setGravity(Vector3(10, 0, 0))
    --_self.rb = lua:getRigidbody(lua:getEntity("testScene2"))
	print(_self.hp)
end

mi_clase["update"] = function (_self, lua)

    _self.hp = _self.hp - 10
    -- if lua:getInputManager():keyPressed(Keycode.A) == true then
    --     lua:instantiate("penguin2")
    -- end
    --local collides = _self.rb:onCollisionEnter("penguin2")
    --if input:keyPressed(Keycode.A) == true then
    --if collides == true then
        --print("colisiono")
    --end 
end

return mi_clase