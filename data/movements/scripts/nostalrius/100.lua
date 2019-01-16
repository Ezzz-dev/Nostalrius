function onStepIn(creature, item, position, fromPosition)
	if creature:isPlayer() and creature:getPlayer():getItemCount(3239) >= 1 and creature:getPlayer():getStorageValue(267) == 0 then
		doRelocate(item:getPosition(),{x = 33178, y = 33016, z = 14})
		item:getPosition():sendMagicEffect(11)
		Game.sendMagicEffect({x = 33178, y = 33016, z = 14}, 11)
		creature:getPlayer():removeItem(3239, 1)
	else
		doRelocate(item:getPosition(),{x = 33025, y = 32872, z = 08})
		item:getPosition():sendMagicEffect(11)
		Game.sendMagicEffect({x = 33025, y = 32872, z = 08}, 11)
	end
end

function onAddItem(item, tileitem, position)
	doRelocate(item:getPosition(),{x = 33025, y = 32872, z = 08})
	item:getPosition():sendMagicEffect(11)
	Game.sendMagicEffect({x = 33025, y = 32872, z = 08}, 11)
end
