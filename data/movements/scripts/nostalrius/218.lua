function onStepIn(creature, item, position, fromPosition)
	doRelocate(item:getPosition(),{x = 32189, y = 31625, z = 04})
end

function onAddItem(item, tileitem, position)
	doRelocate(item:getPosition(),{x = 32189, y = 31625, z = 04})
end
