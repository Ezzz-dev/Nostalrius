function onStepIn(creature, item, position, fromPosition)
	doRelocate(item:getPosition(),{x = 33324, y = 31592, z = 15})
end

function onAddItem(item, tileitem, position)
	doRelocate(item:getPosition(),{x = 33324, y = 31592, z = 15})
end