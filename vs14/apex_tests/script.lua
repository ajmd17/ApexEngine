myvec = nil
x = 99
bob = 100

function mousepress(btn, released)
end

function keypress(key, released)
end

function logic()
	--[[x = x + 1
	if x > 100 then
		bob = bob - 1
		print (bob, " bottles of beer on the wall")
		x = 0
	end--]]
end

function main()
	--[[print ("Math test\n\n")

	print ("vec3: [", myvec.x, ", ", myvec.y, ", ", myvec.z, "]")
	local myvec2 = math.vector3f()
	myvec2:copy(myvec)
	myvec:cross(myvec2)
	print ("vec3: [", myvec.x, ", ", myvec.y, ", ", myvec.z, "]")
	
	local myvec4f = math.vector4f():set(1,2,3,4)
	print ("vec4: [", myvec4f.x, ", ", myvec4f.y, ", ", myvec4f.z, ",", myvec4f.w, "]")
	
	
	local myvec2f = math.vector2f():set(9,9)
	print ("vec2: [", myvec2f.x, ", ", myvec2f.y, "]")
	
	local mymat = math.matrix4f()
	mymat.m10 = 7.0
	print ("mymat: m00", mymat.m00, ", m10", mymat.m10, "]")
	mymat:transpose()
	print ("mymat: m00", mymat.m00, ", m10", mymat.m10, "]")--]]
	
	
	local my_vec2f = math.vector2f():new(1.0, 1.0)
	print ("my_vec2f: x=", my_vec2f.x, ", y=", my_vec2f.y, "]\nAdding a vector[2,5]")
	my_vec2f:add(math.vector2f():new(2, 5))
	print ("my_vec2f: x=", my_vec2f.x, ", y=", my_vec2f.y, "]\nMultiplying by a scalar [6.5]")
	my_vec2f:scale(6.5)
	print ("my_vec2f: x=", my_vec2f.x, ", y=", my_vec2f.y, "]\nMultiplying by a vector [9,9.8]")
	my_vec2f:mult(math.vector2f():new(9, 9.8))
	print ("my_vec2f: x=", my_vec2f.x, ", y=", my_vec2f.y, "]\nTaking the distance between this and [1,1]")
	print ("Distance:", my_vec2f:distance(math.vector2f():new(1,1)))
	
	
	
end