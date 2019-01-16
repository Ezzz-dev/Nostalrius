function onStepIn(creature, item, position, fromPosition)
	if Game.isItemThere({x = 32180, y = 31871, z = 15},3027) and Game.isItemThere ({x = 32173, y = 31871, z = 15},3026) then 
		doRelocate({x = 32177, y = 31869, z = 15},{x = 32177, y = 31863, z = 15})
		Game.sendMagicEffect({x = 32176, y = 31870, z = 15}, 11)
		Game.removeItemOnMap({x = 32173, y = 31871, z = 15}, 3026)
		Game.removeItemOnMap({x = 32180, y = 31871, z = 15}, 3027)
		Game.sendMagicEffect({x = 32173, y = 31871, z = 15}, 3)
		Game.sendMagicEffect({x = 32180, y = 31871, z = 15}, 3)
	else
		doRelocate({x = 32177, y = 31869, z = 15},{x = 32177, y = 31870, z = 15})
		doTargetCombatHealth(0, creature, COMBAT_POISONDAMAGE, -100, -100)
	end
end

function onAddItem(item, tileitem, position)
	doRelocate({x = 32177, y = 31869, z = 15},{x = 32177, y = 31870, z = 15})
end