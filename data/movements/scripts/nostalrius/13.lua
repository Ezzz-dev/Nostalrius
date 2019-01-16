function onStepIn(creature, item, position, fromPosition)
	if creature:isPlayer() then 
		doRelocate({x = 32266, y = 31899, z = 12},{x = 32266, y = 31911, z = 12})
	end
end
