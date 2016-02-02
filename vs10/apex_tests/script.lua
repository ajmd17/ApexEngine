x = 99
bob = 100

function mousepress(btn, released)
end

function keypress(key, released)
end

function logic()
	x = x + 0.5
	if x > 100 then
		bob = bob - 1
		print (bob, " bottles of beer on the wall")
		x = 0
	end
end

function main()
	--[[print ("Hello from Lua!")
	
	local vec0 = Math.Vector3f():new(3.0, 9.0, 9.1)
	print (vec0.x, vec0.y, vec0.z)
	
	local node0 = Scene.Node()
	local node1 = Scene.Node()
	
	node0:setName("Hello")
	node1:setName("World")
	
	node0:add(node1)
	print (node1:getName())
	print (node1:getParent():getName())
	print (node0:size())]]--
	
end