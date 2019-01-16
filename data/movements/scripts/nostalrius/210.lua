function onStepIn(creature, item, position, fromPosition)
	doRelocate(item:getPosition(),{x = 32554, y = 32212, z = 11})
end

function onAddItem(item, tileitem, position)
	doRelocate(item:getPosition(),{x = 32554, y = 32212, z = 11})
end
