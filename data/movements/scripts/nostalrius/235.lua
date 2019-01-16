function onStepIn(creature, item, position, fromPosition)
	doRelocate(item:getPosition(),{x = 33289, y = 32481, z = 6})
end

function onAddItem(creature, item, position, fromPosition)
	doRelocate(item:getPosition(),{x = 33289, y = 32481, z = 6})
end
