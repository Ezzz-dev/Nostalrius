function onStepIn(creature, item, position, fromPosition)
	if creature:isPlayer() and creature:getPlayer():isPaladin() then
		doRelocate(item:getPosition(),{x = 32676, y = 32088, z = 09})
	else
		doRelocate(item:getPosition(),{x = 32641, y = 32141, z = 11})
	end
end

function onAddItem(item, tileitem, position)
	doRelocate(item:getPosition(),{x = 32641, y = 32141, z = 11})
end