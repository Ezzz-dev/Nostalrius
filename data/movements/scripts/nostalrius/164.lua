function onStepIn(creature, item, position, fromPosition)
	if creature:isPlayer() and creature:getPlayer():isKnight() then
		doRelocate(item:getPosition(),{x = 32641, y = 32115, z = 09})
	else
		doRelocate(item:getPosition(),{x = 32641, y = 32141, z = 11})
	end
end

function onAddItem(item, tileitem, position)
	doRelocate(item:getPosition(),{x = 32641, y = 32141, z = 11})
end