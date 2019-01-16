function onStepIn(creature, item, position, fromPosition)
	doRelocate(item:getPosition(),{x = 32725, y = 31589, z = 12})
end

function onAddItem(item, tileitem, position)
	doRelocate(item:getPosition(),{x = 32725, y = 31589, z = 12})
end