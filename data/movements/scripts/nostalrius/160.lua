function onStepIn(creature, item, position, fromPosition)
	doRelocate(item:getPosition(),{x = 32660, y = 32113, z = 08})
end

function onAddItem(item, tileitem, position)
	doRelocate(item:getPosition(),{x = 32660, y = 32113, z = 08})
end