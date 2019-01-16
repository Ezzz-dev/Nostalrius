function onStepIn(creature, item, position, fromPosition)
	if creature:isPlayer() and creature:getPlayer():getItemCount(3241) >= 1 and creature:getPlayer():getStorageValue(265) == 0 then
		doRelocate(item:getPosition(),{x = 33126, y = 32592, z = 15})
		item:getPosition():sendMagicEffect(11)
		Game.sendMagicEffect({x = 33126, y = 32591, z = 15}, 11)
		creature:getPlayer():removeItem(3241, 1)
	else
		doRelocate(item:getPosition(),{x = 33131, y = 32566, z = 08})
		item:getPosition():sendMagicEffect(11)
		Game.sendMagicEffect({x = 33131, y = 32566, z = 08}, 11)
	end
end

function onAddItem(item, tileitem, position)
	doRelocate(item:getPosition(),{x = 33131, y = 32566, z = 08})
	item:getPosition():sendMagicEffect(11)
	Game.sendMagicEffect({x = 33131, y = 32566, z = 08}, 11)
end
