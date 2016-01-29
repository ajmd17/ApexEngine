myvec = nil
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
	print ("Hello from Lua!")
	
	local tmpVec = Math.Vector3f()
	
	local myRoot = Scene.Node()
	myRoot:setName("root")
	
	local myspat = Scene.Node()
	myspat:setName("MySpat")
	
	myRoot:add(myspat)
	
	myspat:setLocalTranslation(tmpVec:set(7.0, 1.0, 1.0))
	myspat:update()
	
	print (myspat:getLocalTranslation().x, myspat:getLocalTranslation().y, myspat:getLocalTranslation().z)
	print (myspat:getGlobalTranslation().x)
	print ("is", myspat:getName(), " attached to root?", myspat:isAttachedToRoot())
	print ("Size of root:", myRoot:size())
	myRoot:removeAt(0)
	myRoot:update()
	print ("is", myspat:getName(), " attached to root?", myspat:isAttachedToRoot())
	print ("Size of root:", myRoot:size())
	
end