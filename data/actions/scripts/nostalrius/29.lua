function onUse(player, item, fromPosition, target, toPosition)
	if item:getId() == 2773 and Game.isItemThere({x = 32220, y = 31845, z = 15}, 2772) and player:getStorageValue(7) ~= 1 then 
		item:transform(2772, 1)
		item:decay()
		item:getPosition():sendMagicEffect(13)
		Game.sendMagicEffect({x = 32217, y = 31842, z = 14}, 12)
		Game.sendMagicEffect({x = 32217, y = 31844, z = 14}, 12)
		Game.sendMagicEffect({x = 32217, y = 31845, z = 14}, 12)
		Game.sendMagicEffect({x = 32218, y = 31844, z = 14}, 12)
		Game.sendMagicEffect({x = 32219, y = 31843, z = 14}, 12)
		Game.sendMagicEffect({x = 32219, y = 31845, z = 14}, 12)
	elseif item:getId() == 2773 then 
		item:getPosition():sendMagicEffect(12)
		doTargetCombatHealth(0, player, COMBAT_FIREDAMAGE, -170, -170)
	end
	return true
end