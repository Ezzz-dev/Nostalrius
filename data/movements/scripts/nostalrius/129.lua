function onStepIn(creature, item, position, fromPosition)
	if creature:isPlayer() and creature:getPlayer():getItemCount(3235) >= 1 and creature:getPlayer():getStorageValue(266) == 0 then
		doRelocate(item:getPosition(),{x = 33051, y = 32777, z = 14})
		item:getPosition():sendMagicEffect(11)
		Game.sendMagicEffect({x = 33051, y = 32777, z = 14}, 11)
		creature:getPlayer():removeItem(3235, 1)
	else
		doRelocate(item:getPosition(),{x = 33133, y = 32642, z = 08})
		item:getPosition():sendMagicEffect(11)
		Game.sendMagicEffect({x = 33133, y = 32642, z = 08}, 11)
	end
end

function onAddItem(item, tileitem, position)
	doRelocate(item:getPosition(),{x = 33133, y = 32642, z = 08})
	item:getPosition():sendMagicEffect(11)
	Game.sendMagicEffect({x = 33133, y = 32642, z = 08}, 11)
end
