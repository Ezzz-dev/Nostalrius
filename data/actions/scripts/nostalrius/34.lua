function onUse(player, item, fromPosition, target, toPosition)
	if item:getId() == 2772 then 
		doRelocate({x = 32636, y = 31881, z = 07},{x = 32636, y = 31881, z = 02})
		item:transform(2773, 1)
		item:decay()
		Game.sendMagicEffect({x = 32636, y = 31881, z = 07}, 3)
		Game.sendMagicEffect({x = 32636, y = 31881, z = 02}, 3)
	elseif item:getId() == 2772 then
		doRelocate({x = 32636, y = 31881, z = 07},{x = 32636, y = 31881, z = 02})
		item:transform(2773, 1)
		item:decay()
		Game.sendMagicEffect({x = 32636, y = 31881, z = 02}, 3)
		Game.sendMagicEffect({x = 32636, y = 31881, z = 07}, 3)
	elseif item:getId() == 2773 then
		doRelocate({x = 32636, y = 31881, z = 02},{x = 32636, y = 31881, z = 07})
		item:transform(2772, 1)
		item:decay()
		Game.sendMagicEffect({x = 32636, y = 31881, z = 07}, 3)
		Game.sendMagicEffect({x = 32636, y = 31881, z = 02}, 3)
	elseif item:getId() == 2773 then
		item:transform(2772, 1)
		item:decay()
		doRelocate({x = 32636, y = 31881, z = 02},{x = 32636, y = 31881, z = 07})
		Game.sendMagicEffect({x = 32636, y = 31881, z = 02}, 3)
		Game.sendMagicEffect({x = 32636, y = 31881, z = 07}, 3)
	end
	return true
end