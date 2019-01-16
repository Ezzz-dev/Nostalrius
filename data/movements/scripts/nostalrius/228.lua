function onStepIn(creature, item, position, fromPosition)
	doRelocate(item:getPosition(),{x = 32776, y = 32255, z = 11})
end

function onAddItem(item, tileitem, position)
	doRelocate(item:getPosition(),{x = 32776, y = 32255, z = 11})
end
