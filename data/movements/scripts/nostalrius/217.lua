function onStepIn(creature, item, position, fromPosition)
	doRelocate(item:getPosition(),{x = 32107, y = 31567, z = 09})
end

function onAddItem(item, tileitem, position)
	doRelocate(item:getPosition(),{x = 32107, y = 31567, z = 09})
end
