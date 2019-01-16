function onStepIn(creature, item, position, fromPosition)
	if creature:isPlayer() then 
		doRelocate({x = 32265, y = 31898, z = 12},{x = 32265, y = 31886, z = 12})
	end
end
