function onStepIn(creature, item, position, fromPosition)
	doRelocate(item:getPosition(),{x = 32836, y = 32294, z = 07})
end

function onAddItem(item, tileitem, position)
	doRelocate(item:getPosition(),{x = 32836, y = 32294, z = 07})
end
