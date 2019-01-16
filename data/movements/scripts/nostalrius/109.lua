function onStepIn(creature, item, position, fromPosition)
	if creature:isPlayer() then 
		doRelocate(item:getPosition(),{x = 33128, y = 32656, z = 15})
		item:getPosition():sendMagicEffect(11)
		Game.sendMagicEffect({x = 33128, y = 32656, z = 15}, 11)
		creature:getPlayer():setStorageValue(259,0)
	end
end

function onAddItem(item, tileitem, position)
	doRelocate(item:getPosition(),{x = 33128, y = 32656, z = 15})
	item:getPosition():sendMagicEffect(11)
	Game.sendMagicEffect({x = 33128, y = 32656, z = 15}, 11)
end
