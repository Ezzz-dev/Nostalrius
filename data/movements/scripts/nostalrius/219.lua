function onStepIn(creature, item, position, fromPosition)
	doRelocate(item:getPosition(),{x = 32081, y = 32172, z = 09})
end

function onAddItem(item, tileitem, position)
	doRelocate(item:getPosition(),{x = 32081, y = 32172, z = 09})
end
